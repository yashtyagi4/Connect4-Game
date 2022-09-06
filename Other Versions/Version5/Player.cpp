/* 
 * File:   Player.cpp
 * Author: Yash Tyagi
 * Created on Dec 1st, 2020, 5:47 PM
 * Purpose:  Player Class and it's attributes and functions
 * Version: 5
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
void Player::print() const{
    cout << "PLAYER " << Plyr.getName() <<  " WITH ID ";
    if(Plyr.getID() == static_cast<ID>(0)) cout << "X ";
    else                                   cout << "O ";
}
