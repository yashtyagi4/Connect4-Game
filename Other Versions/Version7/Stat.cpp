/* 
 * File:         Stat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 1st, 2020, 9:56 PM
 * Purpose:      Stat Class
 * Version:      7
 */

using namespace std;

#include "Stat.h"

//Static member functions
char Stat::games;
char Stat::draws;

//Constructors
Stat::Stat(){
    nmoves  = new char;
    games   = 0;
    draws   = 0;
    tpoints = 0;
    *nmoves = 0;
}

Stat::Stat(char g, char d, char w, char l, int p){
    games   = g;
    draws   = d;
    tpoints = p;
}

//Copy Constructor
Stat::Stat(const Stat &obj){
    nmoves  = new char;
    games   =  obj.games;
    draws   =  obj.draws;
    tpoints =  obj.tpoints;
    *nmoves = *obj.nmoves;
}

//Destructor
Stat::~Stat(){
    delete []nmoves;
}

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
    (*(nmoves + (gNo-1))) = move;
}

//Accessors
char Stat::getGame(){
    return games;
}
char Stat::getDraw(){
    return draws; 
}
char Stat::getPnts() const{
    return tpoints;
}
short Stat::getMoves() const{
    short moves;
    for(int i=0;i < games ;i++){
        moves = moves + (*(nmoves + i));
    }
    return moves;
}

