//
// Created by skony on 2020-05-17.
//

#include <iostream>
#include "GameEngine.h"
GameEngine::GameEngine(Player* p, PlayerView* pv) {
    this->player=p;
    this->playerView=pv;
    state=new StartState;
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
