/* 
 * File:         Pstat.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 7:13 PM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-7 | Pstat Class Body
*/


#ifndef PSTAT_H
#define PSTAT_H

#include "PInfo.h"
#include "Player.h"


class Pstat : public Player, public Stat{
    private:
        char        wins;               //Total number of wins by the player
        char        losses;             //Total number of losses by the player
    public:
        //Constructors
        Pstat();                             //Default
        Pstat(string, ID, char, char, char, char, int, char);
        
        //Copy Constructor
        Pstat(const Pstat &);
        
        //Destructor
        ~Pstat();
        
        //Mutators
        void setWins( char );           //Set wins of the player
        void setLoss( char );           //Set losses of the player
        
        //Accessors
        char getWins() const;           //Get wins of the player
        char getLoss() const;           //Get losses of the player
    
        //Virtual Function redefined from the base class
        virtual void nxtGame() const;
        virtual void getInfo() const;
        
        //Friend Functions of Data Class
        friend class Data;
        
        //Overloaded = operator to fill Pstat with Player data
        void operator=(const Player &p){
            Plyr.setName(p.getName());
            Plyr.setID  (p.getID());
        }
};

#endif /* PSTAT_H */

