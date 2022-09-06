/* 
 * File:   Player.h
 * Author: Yash Tyagi
 * Created on Dec 1st, 2020, 5:47 PM
 * Purpose:  Connect 4 | Project 2 | V1 | Player Class body
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "PInfo.h"

class Player{
private:
    PInfo Plyr;
public:
    //Constructors
    Player();               //Default
    Player(string);
    Player(string, ID);
    
    //Destructor
    ~Player() { }
    
    //Mutators
    void setName(string);
    void setID      (ID);
    
    //Accessors
    string getName() const;
    ID     getID  () const;
    
    //Print the details
    void print() const;
};


#endif /* PLAYER_H */

