/* 
 * File:         Player.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 10:13 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-4 | Player Class body
 */

#ifndef PLAYER_H
#define PLAYER_H

class Player{
protected:
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
    virtual void getInfo() const;
};


#endif /* PLAYER_H */

