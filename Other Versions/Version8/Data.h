/* 
 * File:         Data.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 10:13 AM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-4 | 
 *               Data Class Body + Member functions defined In-line
 */

#ifndef DATA_H
#define DATA_H

#include "Pstat.h"

//Data Class : Friend of Pstat Class
//Data Class member functions are defined inline
class Data{
private:
    vector<char> allWins;
    vector<char> allLoss;
    vector<char> allDraw;
    vector<int>  allPnts;
    vector<char> allMovs;
public:
    //Constructor
    Data(){         //Default
        allWins.clear();
        allLoss.clear();
        allDraw.clear();
        allPnts.clear();
        allMovs.clear(); 
    }             
    
    Data(vector<char> w, vector<char> l, vector<char> d,
         vector<int> p, vector<char> m){
        allWins = w;
        allLoss = l;
        allDraw = d;
        allPnts = p;
        allMovs = m;
    }
    
    //Destructor
    ~Data(){
        allWins.clear();
        allLoss.clear();
        allDraw.clear();
        allPnts.clear();
        allMovs.clear(); 
    }
    
    //Mutators
    void fillTWins(Pstat p){
        allWins[p.games]  = p.wins;
    }
    void fillTLoss(Pstat p){
        allLoss[p.games] = p.losses;
    }
    void fillTDraw(Pstat p){
        allDraw[p.games] = p.draws;       
    }
    void fillTPnts(Pstat p){
        allPnts[p.games] = p.tpoints;
    }
    void fillTMovs(Pstat p){
        allMovs[p.games] = p.getMoves();
    }
    void fillAll  (Pstat p){
        allWins[p.games]  = p.wins;
        allLoss[p.games]  = p.losses;
        allDraw[p.games]  = p.draws;
        allPnts[p.games]  = p.tpoints;
        allMovs[p.games]  = p.getMoves();
    }
    
    //Accessors
    char getTWins(char Gno) const{
        return allWins[Gno-1];
    }
    char getTLoss(char Gno) const{
        return allLoss[Gno-1];
    }
    char getTDraw(char Gno) const{
        return allDraw[Gno-1];
    }
    int  getTPnts(char Gno) const{
        return allPnts[Gno-1];
    }
    char getTMovs(char Gno) const{
    return allMovs[Gno-1];    
    }
    
};

#endif /* DATA_H */

