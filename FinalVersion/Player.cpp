/* 
 * File:         Player.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Player Class
 * Version:      14 (Final)
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
    if(n == "" || n == "\n" || n == " ")
        throw InvldNm();
    else 
    Plyr.setName(n);
}

Player::Player(string n, ID i){
    if(n == "" || n == "\n" || n == " ")
        throw InvldNm();
    else
    Plyr.setName(n);
    Plyr.setID(i);
}

//Mutators:
//Set Name of the Player
void Player::setName(string n){
    if(n == "" || n == "\n" || n == " ")
        throw InvldNm();
    else 
    Plyr.setName(n);
}

//Set ID of the Player
void Player::setID  (ID i){
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
