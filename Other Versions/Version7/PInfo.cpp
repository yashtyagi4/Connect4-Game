/* 
 * File:         Pinfo.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 1st, 2020, 9:56 PM
 * Purpose:      PInfo
 * Version:      7
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
