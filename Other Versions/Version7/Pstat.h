/* 
 * File:         Pstat.h
 * Author:       Yash Tyagi
 * Created :     Dec 1st, 2020, 9:56 PM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-3 | Pstat Class body
 */

#ifndef PSTAT_H
#define PSTAT_H

class Pstat : public Player, Stat{
    private:
        char        wins;               //Total number of wins by the player
        char        losses;             //Total number of losses by the player
    public:
        //Constructors
        Pstat();                             //Default
        Pstat(char, char, char, char, int);
        
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
        virtual void getStat() const;
        virtual void getInfo() const;
};



#endif /* PSTAT_H */

