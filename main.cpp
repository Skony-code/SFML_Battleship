#include <SFML/Graphics.hpp>
#include "src/Model/Player.h"
#include "src/View/PlayerView.h"
#include "src/Controller/GameEngine.h"
#include <iostream>
#include <conio.h>

using namespace std;
int main()
{
    sf::RenderWindow win(sf::VideoMode(500, 1050), "SFML works!");
    Player P1;
    PlayerView PV(P1,&win);
    GameEngine game_engine(&P1,&PV);
    while(win.isOpen())
    {
        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                win.close();
            else
                game_engine.handleEvent(e);
        }
        win.clear();
        game_engine.render();
        win.display();
    }



    /*Player p;
    Player p2;
    PlayerView pv(p,&win);
    p.get_enemy_shots()[1][1]=1;
    p.get_enemy_shots()[1][2]=1;
    p.get_player_shots()[1][1]=1;

    p2.placeShip(0,0,5,1);
    p.placeShip(3,5,4,1);*/
}