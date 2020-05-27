#include <SFML/Graphics.hpp>
#include "Model/Player.h"
#include "View/PlayerView.h"
#include "Controller/GameEngine.h"

using namespace std;
int main()
{
    sf::RenderWindow win(sf::VideoMode(500, 1050), "Battleship");
    Player P1;
    Player P2;
    PlayerView PV(P1,&win);
    GameEngine game_engine(&P1,&P2,&PV);
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
        game_engine.update();
        win.clear();
        game_engine.render();
        win.display();
    }
}