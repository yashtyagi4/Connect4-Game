/* 
 * File:         Player.h
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | Final Version | Player Class Body
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
    
    //Exception Classes
    class InvldNm { };
    
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

