/* 
 * File:         Stat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Stat Class
 * Version:      14 (Final)
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

Stat::Stat(char g, char d, char m, int p){
    games   = g;
    draws   = d;
    moves   = m;
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
void Stat::setMove(char m){
    moves = m;
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

