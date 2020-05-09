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
public:
    Player();
    bool fire(Player p,int x,int y);//returns true if hit
    bool incomingFire(int x,int y);//returns true if hit
    bool placeShip(int x,int y,int length,bool aligment);//1-horizontal 0-vertical, returns true if successful
    bool didLost();
    bool** get_ships();
    bool** get_enemy_shots();
    bool** get_player_shots();
};


#endif //SFML_BATTLESHIP_PLAYER_H
