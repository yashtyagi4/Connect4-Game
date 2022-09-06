/* 
 * File:         Stat.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 12:32 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-5 | Stat Class Body
 */

#ifndef STAT_H
#define STAT_H

//Statistics
class Stat{
protected:
    static char games;              //Total number of games
    static char draws;              //Total number of draws
    int         tpoints;            //Total points earned by the player so far
public:
    //Constructors
    Stat();
    Stat(char, char, int);
    
    //Copy Constructor
    Stat(const Stat &);
    
    //Destructor
    ~Stat();
    
    //Mutators
    void setDraw( char );
    void setGame( char );
    void setPnts( int  );
    void setMove( char, char );
    
    //Accessors
    static char getGame();
    static char getDraw();
    char        getPnts()  const;
    short       getMoves() const;
    
    //Pure Virtual Function
    virtual void getStat() const = 0;
};

#endif /* STAT_H */

