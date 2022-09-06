/* 
 * File:         Data.h
 * Author:       Yash Tyagi
 * Created :     Dec 6th, 2020, 9:12 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | Final Version | Data Class Body
*/
#ifndef DATA_H
#define DATA_H

#include "Pstat.h"
#include "Stat.h"

//Data Class : Friend of Pstat Class
//Data Class member functions are defined inline
class Data{
private:
    const int SIZE = 50;
    char allWins[50];
    char allLoss[50];
    char allDraw[50];
    int  allPnts[50];
    char allMovs[50];
public:
    //Constructor
    Data(){         //Default
        fill(begin(allWins),end(allWins),'\0');
        fill(begin(allLoss),end(allLoss),'\0');
        fill(begin(allDraw),end(allDraw),'\0');
        fill(begin(allPnts),end(allPnts),  0 );
        fill(begin(allMovs),end(allMovs),'\0');
    }             
    
    Data(char w[], char l[], char d[], int p[], char m[]){
        for(int i=0;i<SIZE;i++){
        allWins[i] = w[i];
        allLoss[i] = l[i];
        allDraw[i] = d[i];
        allPnts[i] = p[i];
        allMovs[i] = m[i];
        }
    }
    
    //Copy Constructor
    Data(Data &obj){
        for(int i=0;i<SIZE;i++)
        {
            allWins[i] = obj.allWins[i];
            allLoss[i] = obj.allLoss[i];
            allDraw[i] = obj.allDraw[i];
            allPnts[i] = obj.allPnts[i];
            allMovs[i] = obj.allMovs[i];
        }
    }
    
    //Destructor
    ~Data(){
        fill(begin(allWins),end(allWins),'\0');
        fill(begin(allLoss),end(allLoss),'\0');
        fill(begin(allDraw),end(allDraw),'\0');
        fill(begin(allPnts),end(allPnts),  0 );
        fill(begin(allMovs),end(allMovs),'\0');
    }
    
    //Mutators
    void fillTWins(Pstat p,char gameNo){
        allWins[gameNo] = p.wins;
    }
    void fillTLoss(Pstat p,char gameNo){
        allLoss[gameNo] = p.losses;
    }
    void fillTDraw(Pstat p,char gameNo){
        allDraw[gameNo] = p.draws;       
    }
    void fillTPnts(Pstat p,char gameNo){
        allPnts[gameNo] = p.tpoints;
    }
    void fillTMovs(Pstat p,char gameNo){
        allMovs[gameNo] = p.moves;
    }
    void fillAll  (Pstat p){
        allWins[p.games] = p.wins;
        allLoss[p.games] = p.losses;
        allDraw[p.games] = p.draws;
        allPnts[p.games] = p.tpoints;
        allMovs[p.games] = p.moves;
    }
    
    //Accessors
    char getTWins( char Gno) const{
        return allWins[Gno];
    }
    char getTLoss(char Gno) const{
        return allLoss[Gno];
    }
    char getTDraw( char Gno) const{
        return allDraw[Gno];
    }
    int  getTPnts( char Gno) const{
        return allPnts[Gno];
    }
    char getTMovs(char Gno) const{
        return allMovs[Gno];    
    }
    
};

#endif /* DATA_H */

