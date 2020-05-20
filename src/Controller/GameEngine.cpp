//
// Created by skony on 2020-05-17.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "GameEngine.h"
GameEngine::GameEngine(Player* p1,Player* p2, PlayerView* pv) {
    this->player_1=p1;
    this->player_2=p2;
    this->playerView=pv;
    state=new StartState;
    srand(time(NULL));
}

void GameEngine::handleEvent(sf::Event e) {
    state->handleEvent(*this,e);
}

void GameEngine::update() {
    state->update(*this);
}

void GameEngine::render() {
    state->render(*this);
}
