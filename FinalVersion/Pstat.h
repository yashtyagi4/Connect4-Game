/* 
 * File:         Pstat.h
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | Final Version | Pstat Class Body
*/

#ifndef PSTAT_H
#define PSTAT_H

#include "PInfo.h"
#include "Player.h"
#include "Stat.h"


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
        
        //Template to add
        template <class T>
        int add(T val1, T val2){
            return static_cast<int>(val1 + val2);
        }
        
        //Template to subtract
        template <class T>
        T sub(T val1, T val2){
            if( val1 > val2 )
            return (val1 - val2);
            else (val2 - val1);
        }        
        
        //Overloaded operators
        Pstat operator+(const Pstat  &);
        Pstat operator-(const Pstat  &);
        void  operator=(const Player &);
};

#endif /* PSTAT_H */

