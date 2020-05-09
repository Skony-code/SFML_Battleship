#include <SFML/Graphics.hpp>
#include "src/Model/Player.h"
#include <iostream>

using namespace std;
int main()
{
    Player p;
    p.placeShip(1,1,5,0);
    bool** tab=p.get_ships();
    for(int i;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<tab[i][j];
        }
        cout<<endl;
    }
}