/* 
 * Author: Yash Tyagi
 * Created on October 13, 2020, 9:56 PM
 * Purpose:  Midterm | Project 1 : Connect4 | Final Version | Ch 8 - 12
 */
#ifndef GINFO_H
#define GINFO_H

enum ID { X , O };                  //Two possible ID/Token in the game: X or O

//Statistics about the Player's gameplay
struct Pstat{
    char  wins = 0;                 //Total number of wins by the player
    char  losses;                   //Total number of losses by the player
    char  draws=0;                  //Total number of draws
    char *nmoves = new char;        //No. of moves made by the player in every game
    int   tpoints = 0;              //Total points earned by the player so far 
};

//Player Information
struct PInfo{   
    string name;                    //Name of the player
    ID     plyrID;                  //Player ID/Token in the game
    Pstat  stats;                   //Player's stats
};

#endif /* GINFO_H */

