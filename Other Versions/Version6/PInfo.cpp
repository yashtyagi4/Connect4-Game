/* 
 * File:         PInfo.h
 * Author:       Yash Tyagi
 * Created :     Dec 1st, 2020, 7:34 PM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-2 | PInfo Class
 * Version:      6
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
