//
// Created by skony on 2020-05-11.
//

#include "PlayerView.h"

PlayerView::PlayerView(Player &p, sf::RenderWindow* win) {
    this->p=p;
    this->win=win;
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
            board_one[i][j].setOutlineColor(sf::Color(0,0,0));

            board_two[i][j]=sf::RectangleShape(sf::Vector2f(t_side, t_side));
            board_two[i][j].setPosition(i * t_side, j * t_side + 10 * t_side + bt_height);
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
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(p.get_ships()[i][j]) drawShip(i * t_side, j * t_side + 10 * t_side + bt_height);
            if(p.get_player_shots()[i][j]) drawCross(i * t_side, j * t_side, 4);
            if(p.get_enemy_shots()[i][j]) drawCross(i * t_side, j * t_side + 10 * t_side + bt_height,4);
        }
    }
}

void PlayerView::drawCross(int x,int y,int w) {
    sf::RectangleShape line_1(sf::Vector2f(t_side * 1.414-w-1, w));
    line_1.rotate(45);
    line_1.setPosition(x+w/1.414,y);
    line_1.setFillColor(sf::Color(0,0,0));
    sf::RectangleShape line_2(sf::Vector2f(t_side * 1.414-w-1, w));
    line_2.rotate(-45);
    line_2.setPosition(x, y + t_side-w/1.414-1);
    line_2.setFillColor(sf::Color(0,0,0));
    win->draw(line_1);
    win->draw(line_2);
}

void PlayerView::drawShip(int x, int y) {
    sf::RectangleShape ship(sf::Vector2f(t_side-1,t_side-1));
    ship.setPosition(x,y);
    ship.setFillColor(sf::Color(128,128,128));
    win->draw(ship);
}




