//
// Created by skony on 2020-05-17.
//

#ifndef SFML_BATTLESHIP_STATES_H
#define SFML_BATTLESHIP_STATES_H

#include "GameEngine.h"
class GameEngine;

class State {
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e) = 0;
    virtual void update(GameEngine& GM) = 0;
    virtual void render(GameEngine& GM) = 0;
protected:
    void setState(GameEngine& GM,State* state);
    Player* getPlayer(GameEngine& GM);
    PlayerView* getPlayerView(GameEngine& GM);
};

class StartState : public State
{
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class P1PositioningState : public State
{
private:
    bool aligment;
    int sel_ship_length;
    int sel_ship_quantity[5];//number of ships of length 5-i
public:
    P1PositioningState();
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class P2PositioningState : public State
{
private:
    bool sel_ship_aligment;
    int sel_ship_length;
    int sel_ship_quantity;
public:
    P2PositioningState();
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};


#endif //SFML_BATTLESHIP_STATES_H
