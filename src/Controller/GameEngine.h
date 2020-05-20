//
// Created by skony on 2020-05-17.
//

#ifndef SFML_BATTLESHIP_GAMEENGINE_H
#define SFML_BATTLESHIP_GAMEENGINE_H

#include <SFML/Window/Event.hpp>
#include "../View/PlayerView.h"

#include "States.h"
class State;

class GameEngine {
    friend class State;
private:
    State* state;
    Player* player_1;
    Player* player_2;
    PlayerView* playerView;
public:
    GameEngine(Player* p1,Player* p2, PlayerView* pv);
    void handleEvent(sf::Event e);
    void update();
    void render();
};


#endif //SFML_BATTLESHIP_GAMEENGINE_H
