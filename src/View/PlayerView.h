//
// Created by skony on 2020-05-11.
//

#ifndef SFML_BATTLESHIP_PLAYERVIEW_H
#define SFML_BATTLESHIP_PLAYERVIEW_H

#include <SFML/Graphics.hpp>
#include "../Model/Player.h"

class PlayerView {
private:
    Player p;
    sf::RenderWindow* win;
    sf::RectangleShape board_one[10][10];
    sf::RectangleShape board_two[10][10];
    sf::RectangleShape boarder[10];//this spelling is intentional
    int t_width;
    int t_height;
    void drawShip();
    void drawX();
public:
    PlayerView(Player &p, sf::RenderWindow* win);
    void clear();
    void draw();
};


#endif //SFML_BATTLESHIP_PLAYERVIEW_H
