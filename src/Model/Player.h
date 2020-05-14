//
// Created by skony on 2020-05-09.
//

#ifndef SFML_BATTLESHIP_PLAYER_H
#define SFML_BATTLESHIP_PLAYER_H



class Player {
private:
    bool **ships;
    bool **enemy_shots;
    bool **player_shots;
    bool **player_hits;
public:
    Player();
    void fire(Player p,int x,int y);
    bool incomingFire(int x,int y);//returns true if hit
    bool placeShip(int x,int y,int length,bool aligment);//0-horizontal 1-vertical, returns true if successful
    bool didLost();
    bool** get_ships();
    bool** get_enemy_shots();
    bool** get_player_shots();
    bool** get_player_hits();
};


#endif //SFML_BATTLESHIP_PLAYER_H
