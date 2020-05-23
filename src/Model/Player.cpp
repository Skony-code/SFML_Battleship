//
// Created by skony on 2020-05-09.
//

#include <iostream>
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
    //Checking if ship can be placed
    if((x<0||x+length>10 && !aligment)||(y<0 || y+length>10 && aligment)) return false;
    else
    {
        for(int i=-1;i<2;i++)
        {
            for(int j=-1;j<length+1;j++)
            {
                if(x+i>=0 && x+i<10 && y+j>=0 && y+j<10 && aligment)
                {
                    if (ships[x + i][y + j]) return false;
                }
                else if(x+j>=0 && x+j<10 && y+i>=0 && y+i<10 && !aligment)
                {
                    if(ships[x+j][y+i]) return false;
                }
            }
        }
    }
    //Placing ship
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

bool Player::didSink(int x, int y)
{
    if(checkAligment(x,y))
    {
        int z=1;
        while(y+z<10 && ships[x][y+z])
        {
            if(!enemy_shots[x][y+z])return 0;
            else z++;
        }
        z=1;
        while(y-z>=0 && ships[x][y-z])
        {
            if(!enemy_shots[x][y-z])return 0;
            else z++;
        }
        return 1;
    } else
    {
        int z=1;
        while(x+z<10 && ships[x+z][y])
        {
            if(!enemy_shots[x+z][y])return 0;
            else z++;
        }
        z=1;
        while(x-z>=0 && ships[x-z][y])
        {
            if(!enemy_shots[x-z][y])return 0;
            else z++;
        }
        return 1;
    }
}

bool Player::checkAligment(int x, int y)
{
    if(x>0 && ships[x-1][y]) return 0;
    if(x<9 && ships[x+1][y]) return 0;
    if(y>0 && ships[x][y-1]) return 1;
    if(y<9 && ships[x][y+1]) return 1;
    return 1;
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

