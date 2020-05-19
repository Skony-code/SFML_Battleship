//
// Created by skony on 2020-05-17.
//

#include <iostream>
#include "States.h"
//State
void State::setState(GameEngine& GM,State* state) {
    GM.state=state;
}

Player *State::getPlayer(GameEngine& GM) {
    return GM.player;
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


//P1PositioningState
P1PositioningState::P1PositioningState() {
    aligment=1;
    sel_ship_length=5;
    sel_ship_quantity[0]=1;
    sel_ship_quantity[1]=1;
    sel_ship_quantity[2]=2;
    sel_ship_quantity[3]=3;
    sel_ship_quantity[4]=4;
}

void P1PositioningState::handleEvent(GameEngine& GM,sf::Event e) {
    if(e.type==sf::Event::MouseButtonPressed)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) aligment=!aligment;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            PlayerView::position p=getPlayerView(GM)->getPosition(sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).x,
                    sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).y);
            if(p.board_num==2)
            {
                if(getPlayer(GM)->placeShip(p.x,p.y,sel_ship_length,aligment))
                {
                    sel_ship_quantity[5-sel_ship_length]--;
                    if(sel_ship_quantity[5-sel_ship_length]==0)
                    {
                        if(sel_ship_length>0)
                        {
                            sel_ship_length--;
                        }
                        else
                        {
                            setState(GM,new P2PositioningState);
                        }
                    }
                }
            }
        }
    }
}

void P1PositioningState::render(GameEngine& GM) {
    getPlayerView(GM)->drawBoard();
    getPlayerView(GM)->drawShip(sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).x,
            sf::Mouse::getPosition(*(getPlayerView(GM)->getWin())).y,sel_ship_length,aligment);
}

void P1PositioningState::update(GameEngine &GM) {

}

//P2PositioningState
P2PositioningState::P2PositioningState() {
    sel_ship_aligment=1;
    sel_ship_length=5;
    sel_ship_quantity=1;
}

void P2PositioningState::handleEvent(GameEngine &GM, sf::Event e) {

}

void P2PositioningState::render(GameEngine &GM) {
    getPlayerView(GM)->drawBoard();
}

void P2PositioningState::update(GameEngine &GM) {

}
