/* 
 * File:         PInfo.h
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 10:23 PM
 * Purpose:      Connect 4 | CSC-17A Project 2 | V-8 | PInfo Class Body
*/

#ifndef PINFO_H
#define PINFO_H
#include <string>

enum ID { X , O };                  //Two possible ID/Token in the game: X or O

class PInfo{
protected:
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

