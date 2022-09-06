/* 
 * File:         Player.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 5:23 PM
 * Purpose:      Player Class
 * Version:      10
 */

using namespace std;

//Defined Libraries
#include <iostream>
#include "PInfo.h"
#include "Player.h"

//Constructors
Player::Player(){           //Default
    Plyr.setID(X);
    Plyr.setName("");
}

Player::Player(string n){
    Plyr.setName(n);
}

Player::Player(string n, ID i){
    Plyr.setName(n);
    Plyr.setID(i);
}

//Mutators:
//Set Name of the Player
void Player::setName(string n){
    Plyr.setName(n);
}

//Set ID of the Player
void Player::setID  (ID     i){
    Plyr.setID(i);
}

//Accessors:
//Get Name of the Player
string Player::getName() const{
    return Plyr.getName();
}

//Get ID of the Player
ID     Player::getID()   const{
    return Plyr.getID();
}

//Print Data
void Player::getInfo() const{
    cout << "PLAYER " << Plyr.getName() <<  " WITH ID ";
    if(Plyr.getID() == static_cast<ID>(0)) cout << "X ";
    else                                   cout << "O ";
}
