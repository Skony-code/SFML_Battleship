//
// Created by skony on 2020-05-17.
//

#include <iostream>
#include "States.h"
//State
void State::setState(GameEngine& GM,State* state) {
    GM.state=state;
}

Player *State::getPlayer(GameEngine& GM) {
    return GM.player;
}

PlayerView *State::getPlayerView(GameEngine& GM) {
    return GM.playerView;
}

//Starting State
void StartState::handleEvent(GameEngine& GM,sf::Event e) {
    if(e.type==sf::Event::KeyPressed || e.type==sf::Event::MouseButtonPressed)
        setState(GM,new P1PositioningState);
}

void StartState::render(GameEngine& GM) {
    getPlayerView(GM)->drawStart();
}

void StartState::update(GameEngine &GM) {

}


//P1PositioningState
void P1PositioningState::handleEvent(GameEngine& GM,sf::Event e) {
}

void P1PositioningState::render(GameEngine& GM) {
    getPlayerView(GM)->drawBoard();
}

void P1PositioningState::update(GameEngine &GM) {

}

