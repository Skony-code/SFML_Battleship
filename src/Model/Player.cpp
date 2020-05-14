//
// Created by skony on 2020-05-09.
//

#include "Player.h"

Player::Player() {
    ships=new bool*[10];
    enemy_shots=new bool*[10];
    player_shots=new bool*[10];
    player_hits=new bool*[10];
    for(int i=0;i<10;i++)
    {
        ships[i]=new bool[10];
        enemy_shots[i]=new bool[10];
        player_shots[i]=new bool[10];
        player_hits[i]=new bool[10];
        for(int j=0;j<10;j++)
        {
            ships[i][j]=0;
            enemy_shots[i][j]=0;
            player_shots[i][j]=0;
            player_hits[i][j]=0;
        }
    }
}

void  Player::fire(Player p, int x, int y) {
    player_shots[x][y]=1;
    if(p.incomingFire(x,y))
        player_hits[x][y]=1;
}

bool Player::incomingFire(int x, int y) {
    enemy_shots[x][y]=1;
    if(ships[x][y]) return true;
    else return false;
}

bool Player::placeShip(int x, int y, int length, bool aligment) {
    for(int i=0;i<length;i++)
    {
        if(aligment)
        {
            ships[x][y+i]=1;
        } else
        {
            ships[x+i][y]=1;
        }
    }
    return true;
}

bool Player::didLost() {
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(ships[i][j]&&!enemy_shots[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool** Player::get_ships() {
    return ships;
}

bool** Player::get_enemy_shots() {
    return enemy_shots;
}

bool** Player::get_player_shots() {
    return player_shots;
}

bool **Player::get_player_hits() {
    return player_hits;
}
