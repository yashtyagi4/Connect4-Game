/* 
 * File:         Data.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 5:23 PM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-6 | Data Class Body
 */

#ifndef DATA_H
#define DATA_H

#include <vector>

#include "Pstat.h"
#include "Stat.h"

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
//        allWins.clear();
//        allLoss.clear();
//        allDraw.clear();
//        allPnts.clear();
//        allMovs.clear(); 
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
    void fillTWins(Data &d, Pstat p){
        (d.allWins).push_back(p.wins);
    }
    void fillTLoss(Data &d, Pstat p){
        (d.allLoss).push_back(p.losses);
    }
    void fillTDraw(Data &d, Pstat p){
        (d.allDraw).push_back(p.draws);       
    }
    void fillTPnts(Data &d, Pstat p){
        (d.allPnts).push_back(p.tpoints);
    }
    void fillTMovs(Data &d, Pstat p){
        (d.allMovs).push_back(p.moves);
    }
    void fillAll  (Data &d, Pstat p){
        (d.allWins).push_back(p.wins);
        (d.allLoss).push_back(p.losses);
        (d.allDraw).push_back(p.draws);
        (d.allPnts).push_back(p.tpoints);
        (d.allMovs).push_back(p.moves);
    }
    
    //Accessors
    char getTWins(char Gno) const{
        return allWins[Gno];
    }
    char getTLoss(char Gno) const{
        return allLoss[Gno];
    }
    char getTDraw(char Gno) const{
        return allDraw[Gno];
    }
    int  getTPnts(char Gno) const{
        return allPnts[Gno];
    }
    char getTMovs(char Gno) const{
        return allMovs[Gno];    
    }
    
};

#endif /* DATA_H */

