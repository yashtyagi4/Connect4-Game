/* 
 * File:         PInfo.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 10:23 PM
 * Purpose:      PInfo Class
 * Version:      12
*/

using namespace std;

//Defined Libraries
#include "PInfo.h"

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
