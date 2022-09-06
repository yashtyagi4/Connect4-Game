/* 
 * File:         Stat.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 12:32 AM
 * Purpose:      Stat Class
 * Version:      9
 */
using namespace std;

#include "Stat.h"
#include <cstring>

//Static member functions
char Stat::games;
char Stat::draws;

//Constructors
Stat::Stat(){
    games   = 0;
    draws   = 0;
    tpoints = 0;
}

Stat::Stat(char g, char d, int p){
    games   = g;
    draws   = d;
    tpoints = p;
}

//Copy Constructor
Stat::Stat(const Stat &obj){
    games   =  obj.games;
    draws   =  obj.draws;
    tpoints =  obj.tpoints;
}

//Destructor
Stat::~Stat(){
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

