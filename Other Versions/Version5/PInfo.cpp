/* 
 * File:   PInfo.cpp
 * Author: Yash Tyagi
 * Created on Dec 1st, 2020, 5:47 PM
 * Purpose: Info Class and it's attributes and methods
 * Version: 5
 */

using namespace std;

//Defined Libraries
#include "PInfo.h"
#include "Player.h"

//Mutators:
//Set Name of the Player
void PInfo::setName(string n){
    name   = n;
}

//Set ID of the Player
void PInfo::setID  (ID     i){
    plyrID = i;
}

//Accessors:
//Get Name of the Player
string PInfo::getName() const{
    return name;
}

//Get ID of the Player
ID     PInfo::getID()   const{
    return plyrID;
}
