/* 
 * File:   PInfo.h
 * Author: Yash Tyagi
 * Created on Dec 1st, 2020, 5:47 PM
 * Purpose:  Connect 4 | Project 2 | V1 | PInfo Class Body
 */

#ifndef PINFO_H
#define PINFO_H
#include <string>

enum ID { X , O };                  //Two possible ID/Token in the game: X or O

class PInfo{
private:
    string name;
    ID     plyrID;
public:
    //Constructors : Defined Inline
    PInfo() 
    { name = ""; 
    plyrID = X; 
    }
    PInfo(string n, ID i) 
    { name = n; 
    plyrID = i; 
    }
    
    //Destructor
    ~PInfo() { }
    
    //Mutators
    void setName(string);
    void setID      (ID);
    
    //Accessors
    string getName() const;
    ID     getID  () const;
};

#endif /* PINFO_H */

