//
// Created by skony on 2020-05-17.
//

#include <iostream>
#include "States.h"
//State
void State::setState(GameEngine& GM,State* state) {
    delete GM.state;
    GM.state=state;
}

Player *State::getPlayer1(GameEngine& GM) {
    return GM.player_1;
}
Player *State::getPlayer2(GameEngine& GM) {
    return GM.player_2;
}

PlayerView *State::getPlayerView(GameEngine& GM) {
    return GM.playerView;
}

//Starting State
void StartState::handleEvent(GameEngine& GM,sf::Event e) {
    if(e.type==sf::Event::KeyPressed || e.type==sf::Event::MouseButtonPressed)
        setState(GM,new P1PositioningState);
}

void StartState::render(GameEngine& GM) {
    getPlayerView(GM)->drawStart();
}

void StartState::update(GameEngine &GM) {

}

//PositioningState
PositioningState::PositioningState() {
    sel_ship_quantity[0]=1;
    sel_ship_quantity[1]=1;
    sel_ship_quantity[2]=2;
    sel_ship_quantity[3]=3;
    sel_ship_quantity[4]=4;
}
void PositioningState::randomPositioning(GameEngine &GM,Player* p) {
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<sel_ship_quantity[i];j++)
        {
            bool SHIP_PLACED=false;
            while(!SHIP_PLACED)
            {
                bool rand_aligment=rand()%2;
                int rand_x=rand()%10;
                int rand_y=rand()%10;
                SHIP_PLACED=p->placeShip(rand_x,rand_y,5-i,rand_aligment);
            }
        }
    }
}

//P1PositioningState
P1PositioningState::P1PositioningState() {

    aligment=1;
    sel_ship_length=5;
}

void P1PositioningState::handleEvent(GameEngine& GM,sf::Event e) { //todo ability to select ship by pressing num on keyboard
    if(e.type==sf::Event::MouseButtonPressed)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) aligment=!aligment;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            PlayerView::position p=getPlayerView(GM)->getPosition(
                    sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).x,
                    sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).y);
            if(p.board_num==2)
            {
                if(getPlayer1(GM)->placeShip(p.x,p.y,sel_ship_length,aligment))
                {
                    sel_ship_quantity[5-sel_ship_length]--;
                    if(sel_ship_quantity[5-sel_ship_length]==0)
                    {
                        sel_ship_length--;
                        if(sel_ship_length==0)
                        {
                            setState(GM,new P2PositioningState);
                        }
                    }
                }
            }
        }
    }else if(e.type==sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        randomPositioning(GM,getPlayer1(GM));
        setState(GM,new P2PositioningState);
    }
}

void P1PositioningState::render(GameEngine& GM) {
    getPlayerView(GM)->drawBoard();
    getPlayerView(GM)->drawShip(sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).x,
            sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).y,sel_ship_length,aligment,sf::Color(128,128,128));
}

void P1PositioningState::update(GameEngine &GM) {}

//P2PositioningState
void P2PositioningState::handleEvent(GameEngine &GM, sf::Event e) {}

void P2PositioningState::render(GameEngine &GM) {
    getPlayerView(GM)->drawBoard();
}

void P2PositioningState::update(GameEngine &GM) {
    randomPositioning(GM,getPlayer2(GM));
    setState(GM,new P1TurnState);
}
//P1TurnState
void P1TurnState::handleEvent(GameEngine &GM, sf::Event e) {
    if(e.type==sf::Event::MouseButtonPressed)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            PlayerView::position p=getPlayerView(GM)->getPosition(
                    sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).x,
                    sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).y);
            if(p.board_num==1 && !getPlayer1(GM)->get_player_shots()[p.x][p.y])
            {
                getPlayer1(GM)->fire(*getPlayer2(GM),p.x,p.y);
                ship_sank=0;
                if(getPlayer1(GM)->get_player_hits()[p.x][p.y])
                {
                    if (getPlayer2(GM)->didLost())setState(GM, new GameEndState);
                    if (getPlayer2(GM)->didSink(p.x, p.y)) ship_sank = 1;
                }
                else setState(GM,new P2TurnState);
            }
        }
    }
}

void P1TurnState::render(GameEngine &GM) {
    getPlayerView(GM)->drawBoard();
    if(ship_sank)getPlayerView(GM)->drawSank();
}
void P1TurnState::update(GameEngine &GM) {}

//P2TurnState
void P2TurnState::handleEvent(GameEngine &GM, sf::Event e) {}

void P2TurnState::render(GameEngine &GM) {
    getPlayerView(GM)->drawBoard();
}
void P2TurnState::update(GameEngine &GM) {
    setSuspectedXY(GM);
    getPlayer2(GM)->fire(*getPlayer1(GM),fire_x,fire_y);
    if(!getPlayer2(GM)->get_player_hits()[fire_x][fire_y])setState(GM,new P1TurnState);
    else if(getPlayer1(GM)->didLost())setState(GM,new GameEndState);
}
void P2TurnState::setRandomXY(GameEngine &GM)
{
    int empty_tiles=0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(!getPlayer2(GM)->get_player_shots()[i][j])
            {
                empty_tiles++;
            }
        }
    }
    int rand_shot=rand()%empty_tiles;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(!getPlayer2(GM)->get_player_shots()[i][j])
            {
                if (rand_shot == 0)
                {
                    fire_x=i;
                    fire_y=j;
                    return;
                }
                else
                {
                    rand_shot--;
                }
            }
        }
    }
}

void P2TurnState::setSuspectedXY(GameEngine &GM)
{
    for(int i=0;i<10;i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(getPlayer2(GM)->get_player_hits()[i][j] && !getPlayer1(GM)->didSink(i,j))
            {
                //checking aligment
                bool aligment;
                if(i<9 && getPlayer2(GM)->get_player_hits()[i+1][j]) aligment=0;
                else if(i>0 && getPlayer2(GM)->get_player_hits()[i-1][j]) aligment=0;
                else if(j<9 && getPlayer2(GM)->get_player_hits()[i][j+1]) aligment=1;
                else if(j>0 && getPlayer2(GM)->get_player_hits()[i][j-1]) aligment=1;
                else
                {
                    bool end_flag=0;
                    while(!end_flag)
                    {
                        int dir=rand()%4;
                        switch(dir)
                        {
                            case 0:
                                fire_x=i+1;
                                fire_y=j;
                                break;
                            case 1:
                                fire_x=i-1;
                                fire_y=j;
                                break;
                            case 2:
                                fire_x=i;
                                fire_y=j+1;
                                break;
                            case 3:
                                fire_x=i;
                                fire_y=j-1;
                                break;
                        }
                        if(fire_x>=0 && fire_x<10 && fire_y>=0 && fire_y<10 && !getPlayer2(GM)->get_player_shots()[fire_x][fire_y])
                            end_flag=1;
                    }
                    return;
                }
                //std::cout<<j<<std::endl;
                //predicting ship position acording to aligment
                if(aligment)
                {
                    int z=1;
                    while(j+z<10 && getPlayer2(GM)->get_player_hits()[i][j+z] || !getPlayer2(GM)->get_player_shots()[i][j+z])
                    {
                        if(!getPlayer2(GM)->get_player_shots()[i][j+z])
                        {
                            std::cout<<"1"<<std::endl;
                            fire_x=i;
                            fire_y=j+z;
                            return;
                        }
                        else z++;
                    }
                    z=1;
                    while(j-z>=0 && getPlayer2(GM)->get_player_hits()[i][j-z] || !getPlayer2(GM)->get_player_shots()[i][j-z])
                    {
                        if(!getPlayer2(GM)->get_player_shots()[i][j-z])
                        {
                            std::cout<<"2"<<std::endl;
                            fire_x=i;
                            fire_y=j-z;
                            return;
                        }
                        else z++;
                    }
                }
                else
                {
                    int z=1;
                    while(i+z<10 && getPlayer2(GM)->get_player_hits()[i+z][j] || !getPlayer2(GM)->get_player_shots()[i+z][j])
                    {
                        if(!getPlayer2(GM)->get_player_shots()[i+z][j])
                        {
                            std::cout<<"3"<<std::endl;
                            fire_x=i+z;
                            fire_y=j;
                            return;
                        }
                        else z++;
                    }
                    z=1;
                    while(i-z>=0 && getPlayer2(GM)->get_player_hits()[i-z][j] || !getPlayer2(GM)->get_player_shots()[i-z][j])
                    {
                        if(!getPlayer2(GM)->get_player_shots()[i-z][j])
                        {
                            std::cout<<"4"<<std::endl;
                            fire_x=i-z;
                            fire_y=j;
                            return;
                        }
                        else z++;
                    }
                }
                return;
            }
        }
    }
    setRandomXY(GM);
}

//GameEndState
void GameEndState::handleEvent(GameEngine &GM, sf::Event e) {}

void GameEndState::render(GameEngine &GM) {
    if(getPlayer1(GM)->didLost())getPlayerView(GM)->drawLose();
    else getPlayerView(GM)->drawWin();
}

void GameEndState::update(GameEngine &GM) {}
