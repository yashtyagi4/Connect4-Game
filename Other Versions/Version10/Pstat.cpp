/* 
 * File:         Pstat.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 5:23 PM
 * Purpose:      Pstat Class
 * Version:      10
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
    moves   = 0;
}

Pstat::Pstat(string n, ID i, char g, char d, char w, char l, int p, char m){
    Plyr.setName(n);
    Plyr.setID(i);
    games   = g;
    draws   = d;
    wins    = w;
    losses  = l;
    tpoints = p;
    moves   = m;
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
    moves   =  obj.moves;
}

//Destructor
Pstat::~Pstat(){ }

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
    cout << "PLAYER " << Plyr.getName() << " WITH ID ";
    if(Plyr.getID() == 0) cout << "'X'"; else cout << "'O'"; 
    cout << " AND A TOTAL POINTS OF '" << tpoints <<
            "', YOU ARE THE REAL BOSS!" << endl;
}

//Get Next Game Message (nxtGame)
//Overridden pure virtual function from Pstat's Base class: Stat
void Pstat::nxtGame() const{
    cout << "THAT WAS A GREAT GAME. LET'S SEE WHO'S THE REAL OG IN THIS NEXT GAME!" 
         << endl << endl;;
}
