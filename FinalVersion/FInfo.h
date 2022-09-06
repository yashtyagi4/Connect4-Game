/* 
 * File:         FInfo.h
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | Final Version | FInfo Class Body
*/
#ifndef FINFO_H
#define FINFO_H

//Player Information for File Handling
struct FInfo{   
    string name;                     //Name of the player
    ID     plyrID;                   //Player ID/Token in the game
    char   wins = 0;                 //Total number of wins by the player
    char   losses;                   //Total number of losses by the player
    char   draws=0;                  //Total number of draws
    char  *nmoves = new char;        //No. of moves made by the player in every game
    int    tpoints = 0;              //Total points earned by the player so far 
};

#endif /* FINFO_H */

