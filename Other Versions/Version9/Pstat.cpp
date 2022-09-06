/* 
 * File:         Pstat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 12:32 AM
 * Purpose:      Pstat class
 * Version:      9
 */

using namespace std;

#include <iostream>
#include <iomanip>

#include "PInfo.h"
#include "Player.h"
#include "Stat.h"
#include "Pstat.h"

//Constructor
Pstat::Pstat(){
    Plyr.setName("");
    Plyr.setID(X);
    games   = 0;
    draws   = 0;
    wins    = 0;
    losses  = 0;
    tpoints = 0;
}

Pstat::Pstat(string n, ID i, char g, char d, char w, char l, int p){
    Plyr.setName(n);
    Plyr.setID(i);
    games   = g;
    draws   = d;
    wins    = w;
    losses  = l;
    tpoints = p;
}

//Copy Constructor
Pstat::Pstat(const Pstat &obj){
    Plyr.setName(obj.getName());
    Plyr.setID(obj.getID());
    games   =  obj.games;
    draws   =  obj.draws;
    wins    =  obj.wins;
    losses  =  obj.losses;
    tpoints =  obj.tpoints;
}

//Destructor
Pstat::~Pstat(){
}

//Mutators
void Pstat::setWins( char w ){
    wins = w;
}
void Pstat::setLoss( char l ){
    losses = l;
}

//Accessors
char Pstat::getWins() const{
    return wins;
}
char Pstat::getLoss() const{
    return losses;
}

//Get Player's all Info (GetInfo)
//Redefined function from Pstat's base class: Player
void Pstat::getInfo() const{
    cout << "PLAYER " << Plyr.getName() << " WITH ID " << Plyr.getID() << 
            " AND A TOTAL POINTS OF " << tpoints <<
            ", YOU ARE THE REAL BOSS!" << endl;
}

//Get Player Stat's (GetStat)
//Overridden pure virtual function from Pstat's Base class: Stat
void Pstat::getStat() const{
    cout << "---------------PLAYER STATS------------------" << endl;
    cout << "Wins:  " << static_cast<int>(wins)  << setw(12) << "Losses: " << static_cast<int>(losses) << endl;
    cout << "Draws: " << static_cast<int>(draws) << setw(12) << "Games:  " << static_cast<int>(games)  << endl;
    cout << "Total Points: " << tpoints << endl;
    cout << "---------------------------------------------" << endl;
}
