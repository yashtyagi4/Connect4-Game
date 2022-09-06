/* 
 * File:         Pstat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 10:13 AM
 * Purpose:      Pstat class
 * Version:      8
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
    nmoves  = new char;
    games   = 0;
    draws   = 0;
    wins    = 0;
    losses  = 0;
    tpoints = 0;
    *nmoves = 0;
}

Pstat::Pstat(char g, char d, char w, char l, int p){
    games   = g;
    draws   = d;
    wins    = w;
    losses  = l;
    tpoints = p;
}

//Copy Constructor
Pstat::Pstat(const Pstat &obj){
    nmoves  = new char;
    games   =  obj.games;
    draws   =  obj.draws;
    wins    =  obj.wins;
    losses  =  obj.losses;
    tpoints =  obj.tpoints;
    *nmoves = *obj.nmoves;
}

//Destructor
Pstat::~Pstat(){
    delete []nmoves;
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
    cout << "---------------PLAYER INFO------------------" << endl;
    cout << "PLAYER: " << Plyr.getName() << " with ID: ";
    if(Plyr.getID() == static_cast<ID>(0)) cout << "X" << endl;
    else                                   cout << "O" << endl;
    cout << "Wins:  " << static_cast<int>(wins)  << setw(12) << "Losses: " << static_cast<int>(losses) << endl;
    cout << "Draws: " << static_cast<int>(draws) << setw(12) << "Games:  " << static_cast<int>(games)  << endl;
    cout << "Total Points: " << tpoints << setw(12) << "Moves: " << getMoves() << endl;
    cout << "---------------------------------------------" << endl;
}

//Get Player Stat's (GetStat)
//Overridden pure virtual function from Pstat's Base class: Stat
void Pstat::getStat() const{
    cout << "---------------PLAYER STATS------------------" << endl;
    cout << "Wins:  " << static_cast<int>(wins)  << setw(12) << "Losses: " << static_cast<int>(losses) << endl;
    cout << "Draws: " << static_cast<int>(draws) << setw(12) << "Games:  " << static_cast<int>(games)  << endl;
    cout << "Total Points: " << tpoints << setw(12) << "Moves: " << getMoves() << endl;
    cout << "---------------------------------------------" << endl;
}
