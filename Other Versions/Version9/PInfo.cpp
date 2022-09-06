/* 
 * File:         PInfo.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 12:32 AM
 * Purpose:      PInfo Class body
 * Version:      9
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
