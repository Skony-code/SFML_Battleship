//
// Created by skony on 2020-05-11.
//

#ifndef SFML_BATTLESHIP_PLAYERVIEW_H
#define SFML_BATTLESHIP_PLAYERVIEW_H

#include <SFML/Graphics.hpp>
#include "../Model/Player.h"

class PlayerView {
private:
    std::vector<bool> scores;
    sf::Font font;
    Player p;
    sf::RenderWindow* win;
    sf::RectangleShape board_one[10][10];
    sf::RectangleShape board_two[10][10];
    sf::RectangleShape boarder[10];//this spelling is intentional
    int t_side;
    int bt_width;
    int bt_height;
    bool isInside(sf::RectangleShape &rect,int x,int y);
    void drawCross(int x, int y, int w,sf::Color c);
    void drawShipTile(int x,int y,sf::Color c);
    void loadScores();
public:
    PlayerView(Player &p, sf::RenderWindow* win);
    void drawBoard();
    void drawWin();
    void drawLose();
    void drawStart();
    void drawSank();
    void drawScores();
    void drawShip(int x,int y,int length,bool aligment,sf::Color c);
    struct position
    {
        int board_num;
        int x;
        int y;
    };
    position getPosition(int x,int y);
    sf::RenderWindow* getWin();
};


#endif //SFML_BATTLESHIP_PLAYERVIEW_H
