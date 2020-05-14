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
    PlayerView pv(p,&win);
    p.get_enemy_shots()[1][1]=1;
    p.get_enemy_shots()[1][2]=1;
    p.get_player_shots()[1][1]=1;
    //p.get_player_shots()[1][2]=1;
    p.placeShip(3,5,4,1);
    while(win.isOpen())
    {
        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                win.close();
        }
        win.clear();
        pv.draw();
        win.display();
    }
}