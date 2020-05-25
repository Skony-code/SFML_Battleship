//
// Created by skony on 2020-05-11.
//

#include "PlayerView.h"
#include<iostream>
#include <fstream>

PlayerView::PlayerView(Player &p, sf::RenderWindow* win) {
    this->p=p;
    this->win=win;
    loadScores();
    font.loadFromFile("Arial.ttf");
    t_side= win->getSize().x / 10;
    bt_width=win->getSize().x / 10;
    bt_height=win->getSize().y / 21;
    for(int i=0;i<10;i++)
    {
        boarder[i]=sf::RectangleShape(sf::Vector2f(bt_width, bt_height));
        boarder[i].setPosition(i * t_side, 10 * t_side);
        boarder[i].setOutlineThickness(1);
        boarder[i].setOutlineColor(sf::Color(0,0,0));
        boarder[i].setFillColor(sf::Color(70,70,70));
        for(int j=0;j<10;j++)
        {
            board_one[i][j]=sf::RectangleShape(sf::Vector2f(t_side, t_side));
            board_one[i][j].setPosition(i * t_side, j * t_side);
            board_one[i][j].setOutlineThickness(1);
            board_one[i][j].setOutlineColor(sf::Color(40,185,0));
            board_one[i][j].setFillColor(sf::Color(0,0,0));

            board_two[i][j]=sf::RectangleShape(sf::Vector2f(t_side, t_side));
            board_two[i][j].setPosition(i * t_side, j * t_side + 10 * t_side + bt_height);
            board_two[i][j].setOutlineThickness(1);
            board_two[i][j].setOutlineColor(sf::Color(0,0,0));
            board_two[i][j].setFillColor(sf::Color(66,120,255));
        }
    }
}

void PlayerView::drawBoard() {
    for(int i=0;i<10;i++)
    {
        win->draw(boarder[i]);
        for(int j=0;j<10;j++)
        {
            win->draw(board_one[i][j]);
            win->draw(board_two[i][j]);
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(p.get_ships()[i][j]) drawShipTile(i * t_side, j * t_side + 10 * t_side + bt_height,sf::Color(128,128,128));
            if(p.get_player_shots()[i][j] && p.get_player_hits()[i][j]) drawShipTile(i * t_side, j * t_side,sf::Color(40,185,0));
            else if(p.get_player_shots()[i][j]) drawCross(i * t_side, j * t_side, 4,sf::Color(40,185,0));
            if(p.get_enemy_shots()[i][j]) drawCross(i * t_side, j * t_side + 10 * t_side + bt_height,4,sf::Color(0,0,0));
        }
    }
}

void PlayerView::drawCross(int x,int y,int w,sf::Color c) {
    sf::RectangleShape line_1(sf::Vector2f(t_side * 1.414-w-1, w));
    line_1.rotate(45);
    line_1.setPosition(x+w/1.414,y);
    line_1.setFillColor(c);
    sf::RectangleShape line_2(sf::Vector2f(t_side * 1.414-w-1, w));
    line_2.rotate(-45);
    line_2.setPosition(x, y + t_side-w/1.414-1);
    line_2.setFillColor(c);
    win->draw(line_1);
    win->draw(line_2);
}

void PlayerView::drawShipTile(int x, int y,sf::Color c) {
    sf::RectangleShape ship(sf::Vector2f(t_side-1,t_side-1));
    ship.setPosition(x,y);
    ship.setOutlineThickness(1);
    ship.setOutlineColor(sf::Color(0,0,0));
    ship.setFillColor(c);
    win->draw(ship);
}

bool PlayerView::isInside(sf::RectangleShape &rect,int x,int y) {
    return (x > rect.getPosition().x &&
           x < rect.getPosition().x + rect.getSize().x &&
           y > rect.getPosition().y &&
           y < rect.getPosition().y + rect.getSize().y);
}

PlayerView::position PlayerView::getPosition(int x,int y) {
    position pos;
    for(int i=0;i<10;i++)
    {
        if(isInside(boarder[i],x,y))
        {
            pos.board_num=3;
            pos.x=i;
            pos.y=0;
            return  pos;
        }
        for(int j=0;j<10;j++)
        {
            if(isInside(board_one[i][j],x,y))
            {
                pos.board_num=1;
                pos.x=i;
                pos.y=j;
                return  pos;
            }
            else if(isInside(board_two[i][j],x,y))
            {
                pos.board_num=2;
                pos.x=i;
                pos.y=j;
                return pos;
            }
        }
    }
}

void PlayerView::drawStart() {
    sf::Text text;
    text.setFont(font);
    text.setString("Battleships");
    text.setCharacterSize(48); // in pixels, not points!
    text.setPosition(win->getSize().x/2-text.getGlobalBounds().width/2,win->getSize().y/4-text.getGlobalBounds().height/2);
    text.setFillColor(sf::Color(40,185,0));
    win->draw(text);
}

void PlayerView::drawShip(int x,int y,int length,bool aligment,sf::Color c) {
    for(int i=0;i<length;i++)
    {
        if(!aligment) drawShipTile(x+i*t_side,y,c);
        else drawShipTile(x,y+i*t_side,c);
    }
}

void PlayerView::drawWin() {
    sf::Text text;
    text.setFont(font);
    text.setString("You Win");
    text.setCharacterSize(48); // in pixels, not points!
    text.setPosition(win->getSize().x/2-text.getGlobalBounds().width/2,win->getSize().y/2-text.getGlobalBounds().height/2);
    text.setFillColor(sf::Color(40,185,0));
    win->draw(text);
}

void PlayerView::drawLose() {
    sf::Text text;
    text.setFont(font);
    text.setString("You Lose");
    text.setCharacterSize(48); // in pixels, not points!
    text.setPosition(win->getSize().x/2-text.getGlobalBounds().width/2,win->getSize().y/2-text.getGlobalBounds().height/2);
    text.setFillColor(sf::Color(40,185,0));
    win->draw(text);
}

sf::RenderWindow *PlayerView::getWin() {
    return win;
}

void PlayerView::drawSank()
{
    sf::Text text;
    text.setFont(font);
    text.setString("Ship Sank !!!");
    text.setCharacterSize(48); // in pixels, not points!
    text.setPosition(win->getSize().x/2-text.getGlobalBounds().width/2,win->getSize().y/2-text.getGlobalBounds().height/2-12);
    text.setFillColor(sf::Color(40,185,0));
    win->draw(text);
}

void PlayerView::drawScores()
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(36); // in pixels, not points!
    text.setFillColor(sf::Color(40,185,0));
    text.setString("Last Scores:");
    text.setPosition(win->getSize().x / 2 - text.getGlobalBounds().width / 2,
                     win->getSize().y / 4 - text.getGlobalBounds().height / 2 + 150);
    win->draw(text);
    for(int i=scores.size()-1;i>=0;i--)
    {
        std::string s="x.Player y won.";
        s[0]=(char)(i+49);
        s[9]=scores[5-i]+49;
        text.setString(s);
        text.setPosition(win->getSize().x / 2 - text.getGlobalBounds().width / 2,
                         win->getSize().y / 4 - text.getGlobalBounds().height / 2 + 200 +i*50);
        win->draw(text);
    }
}

void PlayerView::loadScores()
{
    std::ifstream file("Scores.txt");
    std::string winner;
    while(std::getline(file,winner))
    {
        scores.push_back( (winner=="0")? 0:1);
        if(scores.size()>5) scores.erase(scores.begin());
    }
    file.close();
}
