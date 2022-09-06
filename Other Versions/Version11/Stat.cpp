/* 
 * File:         Stat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 7:13 PM
 * Purpose:      Stat Class
 * Version:      11
*/

using namespace std;

#include "Stat.h"

//Static member functions
char Stat::games;
char Stat::draws;

//Constructors
Stat::Stat(){
    games   = 0;
    draws   = 0;
    tpoints = 0;
    moves   = 0;
}

Stat::Stat(char g, char d, char w, char l, int p){
    games   = g;
    draws   = d;
    tpoints = p;
}

//Copy Constructor
Stat::Stat(const Stat &obj){
    games   =  obj.games;
    draws   =  obj.draws;
    tpoints =  obj.tpoints;
    moves   =  obj.moves;
}

//Destructor
Stat::~Stat() { }

//Mutators
void Stat::setDraw( char d){
    draws  = d;
}
void Stat::setGame( char g){
    games  = g;
}
void Stat::setPnts( int  p){
    tpoints = p;
}
void Stat::setMove(char gNo, char move){
    moves = moves + move;
}

//Accessors
char Stat::getGame(){
    return games;
}
char Stat::getDraw(){
    return draws; 
}
int Stat::getPnts() const{
    return tpoints;
}
short Stat::getMoves() const{
    return moves;
}

