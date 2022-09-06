/* 
 * File:         main.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 1st, 2020, 5:47 PM
 * Purpose:      Connect 4 Game
 * Version:      5
 * Description:  From this Version, the game will be implement from scratch and 
 *               with a different approach, implementing classes instead of struct.
 *               The purpose of this version is to create PInfo and Player
 *               classes and implement their aggregation relation. 
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//Defined Files
#include "PInfo.h"
#include "Player.h"

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {  
    //Declare all variables
    Player player("Yash",O);
    
    //Initialize Variables
    
    //Display Outputs
    player.print();
    
    //Exist Stage Right
    return 0;
}