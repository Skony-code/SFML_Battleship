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