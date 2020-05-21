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
    Player* getPlayer1(GameEngine& GM);
    Player* getPlayer2(GameEngine& GM);
    PlayerView* getPlayerView(GameEngine& GM);
};

class StartState : public State
{
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class PositioningState : public State
{
protected:
    int sel_ship_quantity[5];//number of ships of length 5-i
    void randomPositioning(GameEngine &GM,Player* p);
public:
    PositioningState();
    virtual void handleEvent(GameEngine& GM,sf::Event e)=0;
    virtual void render(GameEngine& GM)=0;
    virtual void update(GameEngine& GM)=0;
};

class P1PositioningState : public PositioningState
{
private:
    bool aligment;
    int sel_ship_length;
public:
    P1PositioningState();
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class P2PositioningState : public PositioningState
{
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class P1TurnState : public State
{
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};

class P2TurnState : public State
{
private:
    void fireAtRandom(GameEngine& GM);
public:
    virtual void handleEvent(GameEngine& GM,sf::Event e);
    virtual void render(GameEngine& GM);
    virtual void update(GameEngine& GM);
};
#endif //SFML_BATTLESHIP_STATES_H
