//
// Created by skony on 2020-05-11.
//

#include "PlayerView.h"

PlayerView::PlayerView(Player &p, sf::RenderWindow* win) {
    this->p=p;
    this->win=win;
    t_width=win->getSize().x/10;
    t_height=win->getSize().y/21;
    for(int i=0;i<10;i++)
    {
        boarder[i]=sf::RectangleShape(sf::Vector2f(t_height,t_width));
        boarder[i].setPosition(i*t_width,10*t_height);
        boarder[i].setOutlineThickness(1);
        boarder[i].setOutlineColor(sf::Color(0,0,0));
        boarder[i].setFillColor(sf::Color(100,100,100));
        for(int j=0;j<10;j++)
        {
            board_one[i][j]=sf::RectangleShape(sf::Vector2f(t_width,t_height));
            board_one[i][j].setPosition(i*t_width,j*t_height);
            board_one[i][j].setOutlineThickness(1);
            board_one[i][j].setOutlineColor(sf::Color(0,0,0));

            board_two[i][j]=sf::RectangleShape(sf::Vector2f(t_width,t_height));
            board_two[i][j].setPosition(i*t_width,j*t_height+11*t_height);
            board_two[i][j].setOutlineThickness(1);
            board_two[i][j].setOutlineColor(sf::Color(0,0,0));
        }
    }
}

void PlayerView::draw() {
    for(int i=0;i<10;i++)
    {
        win->draw(boarder[i]);
        for(int j=0;j<10;j++)
        {
            win->draw(board_one[i][j]);
            win->draw(board_two[i][j]);
        }
    }
}




