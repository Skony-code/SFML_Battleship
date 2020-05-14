#include <SFML/Graphics.hpp>
#include "src/Model/Player.h"
#include "src/View/PlayerView.h"
#include <iostream>
#include <conio.h>

using namespace std;
int main()
{
    sf::RenderWindow win(sf::VideoMode(500, 1050), "SFML works!");
    Player p;
    Player p2;
    PlayerView pv(p,&win);
    p.get_enemy_shots()[1][1]=1;
    p.get_enemy_shots()[1][2]=1;
    p.get_player_shots()[1][1]=1;

    p2.placeShip(0,0,5,1);
    p.placeShip(3,5,4,1);
    while(win.isOpen())
    {
        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                win.close();
            if(e.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                PlayerView::position pos=pv.getPosition(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y);
                //cout<<pos.board_num<<pos.x<<" "<<pos.y<<endl;
                if(pos.board_num==1) p.fire(p2,pos.x,pos.y);
            }
        }
        win.clear();
        pv.draw();
        win.display();
    }
}