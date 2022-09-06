/* 
 * File:         main.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 2st, 2020, 5:23 PM
 * Purpose:      Connect 4 Game
 * Version:      10
 * Description:  The purpose of this version is to implement the Pstat class 
 *               into the game (main.cpp) and also count the stats accordingly
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

//Defined Files
#include "PInfo.h"
#include "Player.h"
#include "Stat.h"
#include "Data.h"

//Global Constants only
//Math, Physics, Conversions, Higher Order Dimension

//Function Prototypes
//Display Rules of the game
void   rules  (); 
//Get the info of the player
Player GetInfo(int);  
//Display the Board after each turn
void   disBrd (char *, const int, const int);
//Get the Player choice of drop
char   choice (char *, Player);      
//Drop the player's choice in board
void   drop   (char [][7], Player , const char, const int); 
//Check if the player's patterns connects
bool   connect(Player *, char[][7], const int, const int);
//Check if Player won, and display the winning message
void   plyrwon(Player *, int, char [][4], Pstat, Data); 
//Ask players to play more
bool   plymore(char *, const int, const int);
//Check if Game board is full
char   brdFull(char [][7], const int);      
//Get Info of the player based on the requirement (calls virtual functions)
void   getNtfn(const Player &);
//Get Statistics of the player in middle of the game (calls virtual function)
void   nextPly(const Stat &);

//Execution Begins Here
int main(int argc, char** argv) {  
    enum plyrnum { P1 , P2 };            //Player 1 : P1 and Player 2 : P2 Enum
    
    //Declare all variables 
    const int tplayer = 2;               //Total number of players
    const int brdrows = 6;               //Number of rows in the board
    const int brdcols = 7;               //Number of columns in the board
    const int tstats = 5;                //To store total stats of a Player
    char      tmoves[tplayer];           //Total number of moves by each player
    char      board[brdrows][brdcols];   //Game Board 2-D grid
    char     *brdPtr = (char*)board;     //Pointer to board array
    char      dropPos;                   //Drop position specified by the user
    char      playagn;                   //To store if players want to play again
    Player    players[tplayer];          //Players Main Infomation
    Player   *plyrptr[tplayer];          //Array of pointers to players class
    bool      currwin;                   //Current winner of the present game
    bool      full;                      //To store True if the board is full      
    int       gameNo;                    //Total number of games
    ID        id;                        //ID of the player    
    bool      again;                     //To store the answer if Players wants
                                         //to play another game or not
    string    GStart;                    //To notify the players that the game has started
    Pstat     PLAYER1;                   //To store Player 1 Info along with Stats
    Data      PData1;                    //To store all the data for each game of Player 1
    Data      PData2;                    //To store all the data for each game of Player 2
    int       points1;                   //Calculate the points for Player 1
    int       points2;                   //Calculate the points for Player 2
    
    //Initialize Variables
    
    //To store players stats: 
    //Index 0 : Wins  |  Index 1 : Losses | Index 2 : Draws | Index 3 : Moves;
    char stats[tplayer][tstats-1] =  { {'\0','\0','\0','\0'},
                                       {'\0','\0','\0','\0'}};
    currwin = false;
    full = false;
    gameNo = 0;
    GStart = "\0";
    points1 = 0;
    points2 = 0;

    //Displaying the rules and instructions of the game
    rules();
    
    //Taking names of the players and assigning them their game ID
    players[0] = GetInfo(0);
    players[1] = GetInfo(1);
    
    //Notify the players that the game has started
    getNtfn(players[P1]);
    GStart.append(" and "); cout << GStart << endl;
    getNtfn(players[P2]); 
    GStart.clear();
    GStart.append(", GAME BEGINS! LET'S GO!"); cout << GStart << endl;
    
    //Displaying the board
    disBrd(brdPtr, brdrows, brdcols);
    
    //Filling PLAYER 1 object with Player info using = operator
    PLAYER1 = players[static_cast<int>(P1)];
    //Filling PLAYER 2 object using constructor
    Pstat PLAYER2(players[static_cast<int>(P2)].getName() , 
          players[static_cast<int>(P2)].getID() ,'\0','\0','\0','\0', 0, '\0');
    
    //Game Begins here--->
    do { 
        
        again = true; //Making play again True until specified as False
        
        //Both players turn for 1 time
        for (plyrnum P = P1; P <= P2; P = static_cast<plyrnum>(P+1)) {
            
        //Storing the valid drop position specified in by the player
        dropPos = choice(brdPtr, players[static_cast<int>(P)]);

        //Dropping the Player's Token at the specified position
        drop(board, players[static_cast<int>(P)], dropPos, brdrows);
        
        //Displaying the updated board
        disBrd(brdPtr, brdrows, brdcols);

        //Initializing the pointer to the specific player's structure
        plyrptr[static_cast<int>(P)] = &players[static_cast<int>(P)];         
        
        //Counting moves of the player for the game
        stats[static_cast<int>(P)][3]++;
        if(static_cast<int>(P) == 0)
             PLAYER1.setMove(gameNo,stats[static_cast<int>(P)][3]);
        else PLAYER2.setMove(gameNo,stats[static_cast<int>(P)][3]);

        PLAYER1.setGame(static_cast<char>(gameNo));     //Updating games
        
        //Filling the moves of this game in Player's data
        if(static_cast<int>(P) == 0)
        PData1.fillTMovs(PData1, PLAYER1);
        else PData2.fillTMovs(PData1, PLAYER2);
        
        //Checking if the player won
        if( connect(plyrptr[P] , board, brdrows, brdcols) ) {   
            
            //Updating the losses
            ( static_cast<int>(P) == 0 ? stats[P2][1]++ : stats[P1][1]++ );
            PLAYER1.setLoss(stats[P1][1]);
            PLAYER2.setLoss(stats[P2][1]);
            
            //Filling the losses of this game in Player's data
            if(static_cast<int>(P) == 0)
            PData1.fillTLoss(PData1, PLAYER1);
            else PData2.fillTLoss(PData1, PLAYER2);
            
            //Updating the total points
            if(static_cast<int>(P) == 0){
                points1 = points1 + (42 - static_cast<int>(stats[P][3]))*10;
                PLAYER1.setPnts(points1);
                PData1.fillTPnts(PData1,PLAYER1);
            }
            else {
                points2 = points2 + (42 - static_cast<int>(stats[P][3]))*10;
                PLAYER2.setPnts(points2);
                PData2.fillTPnts(PData2,PLAYER1);  
            }
            
            //Notifying Winner and counting total wins and losses
            if(static_cast<int>(P) == 0)
            plyrwon(plyrptr[P], gameNo, stats, PLAYER1, PData1);
            else plyrwon(plyrptr[P], gameNo, stats, PLAYER2, PData2);
            
            gameNo++;
            
            //Asking players if they want to play more
            again = plymore(brdPtr, brdrows, brdcols);
            if( again ) {
                
            //Making the number of moves 0 for next game
            stats[P1][3] = '\0';
            stats[P2][3] = '\0';
            cout << endl << endl << endl;
            
            //Notifying Players that the game has begin
            nextPly(PLAYER1);
            
            disBrd(brdPtr, brdrows, brdcols);         //Displaying the Board
            break; }
            else break;
        }  
    }
     //Checking if the board is full
     if( static_cast<int>( brdFull(board, brdcols) ) == 7 ){
         cout << "THE BOARD IS FULL, IT IS A DRAW!" << endl;
         again = plymore(brdPtr, brdrows, brdcols);
         
         //Displaying the Board
         if(again == true) disBrd(brdPtr, brdrows, brdcols);
     }
    }while(again);
    
    //Exit Stage Right
    cout << endl << "Thank you for playing!" << endl;
    return 0;
}

//__________________________________________________________________________

//Get Info of the player based on the requirement (calls virtual functions)
void   getNtfn(const Player &P){
    P.getInfo();
}

//__________________________________________________________________________

//Get Statistics of the player in middle of the game (calls virtual function)
void   nextPly(const Stat &S){
    S.nxtGame();
}

//__________________________________________________________________________

//Displaying the rules and instructions of the game
void rules(){
    cout << "WELCOME TO CONNECT 4!" << endl
         << "It's a two-player game, in which each player is assigned one of the" << endl
         << "two disk { X , O }. When the turn will come each player will drop" << endl
         << "his/her disc into a seven-column, six-row vertically suspended grid." << endl
         << "The pieces fall straight down, occupying the lowest available" << endl
         << "space within the column." << endl << endl
         << "The OBJECTIVE of the game is to be the first to form a horizontal," << endl
         << "vertical, or diagonal line of four of one's own discs." << endl << endl;
}

//__________________________________________________________________________

//Taking names of the players and assigning them their game ID
Player GetInfo(int P)
{
    Player    plyr;
    string    name;                      //Name of the player
    if(P == 0)
    cout << "Player 1 Enter your name: ";
    else cout << "Player 2 Enter your name: ";
    getline(cin, name, '\n');
    plyr.setName(name);
    plyr.setID(static_cast<ID>(P));
    
    return plyr;
}


//__________________________________________________________________________

//Displaying Board
void disBrd(char *brdPtr, const int rows, const int cols){
    
    //Border
    for(int i=0;i<29;i++)
        cout << "_";
    cout << endl;
    
    //Column index in Board
    for(int j=1;j<8;j++)  
        cout << setw(3) << j << " ";
    cout << endl;
    
    //Border
    for(int i=0;i<29;i++)
        cout << "_";
    cout << endl;
    
    //Printing the board
    for(int index = 0; index < rows*cols; index++) { 
        
        //Checking if the space is already filled with a token
        if( *(brdPtr + (index)) != 'X' && *(brdPtr + (index)) != 'O')
            *(brdPtr + (index)) = ' ';
        cout << "| " << *(brdPtr + (index)) << " ";
        
        if((index+1)%7==0)
            cout << '|' << endl;
    }
    
    //Border
    for(int i=0;i<29;i++)
        cout << '_' ;
    cout << endl << endl;
}

//__________________________________________________________________________

//Asking for player's choice of drop in which index
char choice( char *brdPtr, Player plyr ){
    char index;
    
    do{
        cout << plyr.getName() << "'s Turn! Your token is: ";
        if(plyr.getID() == X) cout << "X" << endl; else cout << "O" << endl;
        
        
        cout << "Please choose a valid column index between 1 and 7 to drop your token: ";
        cin >> index;
        index = index - 49;
        
        //Checking if the specified column is full
        while ( *(brdPtr + (static_cast<int>(index))) == 'X' ||
                *(brdPtr + (static_cast<int>(index))) == 'O' )
            {
                    cout << "That column is full, please choose a new column: ";
                    cin  >> index;
                    index = index - 49;
            }
    }while(index < 0 || index > 6);
    
    cout << endl;
    return index;
}

//__________________________________________________________________________

//Dropping the token in specified column
void drop( char board[][7], Player plyr, const char dropPos, const int rows)
{
	int row = rows-1;
        bool done;
	done = false;

	do 
	{
            if ( board[row][static_cast<int>(dropPos)] != 'X' 
              && board[row][static_cast<int>(dropPos)] != 'O' )
            {
                    board[row][static_cast<int>(dropPos)] = (plyr.getID() == X? 'X' : 'O');
                    done = true;
            }
		else (--row);
	} while( done != true );
}

//__________________________________________________________________________

//Checking if connection was made or not
bool connect(Player *plyrptr, char board[][7], const int rows, const int cols)
{
    char token;                     //Player ID
    bool win;                       //To store the result if player won or not
    
    if(plyrptr->getID() == X) token = 'X';
    else token = 'O';
    
    win = false;
    
    for(int row = rows-1; row >= 0; --row) {
        
        for(int col = cols-1; col >= 0; --col) {   
            //Check for negative slope diagonal connection
            if( board[row][col]     == token &&
                board[row-1][col-1] == token &&
                board[row-2][col-2] == token &&
                board[row-3][col-3] == token &&
                col >= 3 && row >= 3)
                win = true;

            //Check for straight horizontal line connection
            if( board[row][col]   == token &&
                board[row][col-1] == token &&
                board[row][col-2] == token &&
                board[row][col-3] == token &&
                col >= 3)
                win = true;
            //Checking for straight vertical line connection
            if( board[row][col]   == token &&
                board[row-1][col] == token &&
                board[row-2][col] == token &&
                board[row-3][col] == token &&
                row >= 3)	
                win = true;

            //Checking for positive slope diagonal connection
            if( board[row][col]     == token &&
                board[row-1][col+1] == token &&
                board[row-2][col+2] == token &&
                board[row-3][col+3] == token &&
                row >= 3 && col <= 3 )
                win = true;
        }
	}

return win;
}

//__________________________________________________________________________

//Notifying Player won
void plyrwon(Player *plyrptr, int gameNo, char stats[][4], Pstat PLAYER, Data PData)
{   
    //Updating the total wins
    if(plyrptr->getID() == 0){
        stats[0][0]++;
        PLAYER.setWins(stats[0][0]);
    }
    else {
        stats[1][0]++;
        PLAYER.setWins(stats[1][0]);
    }
    PData.fillTWins(PData, PLAYER);     //Filling the wins of of the player for this game
    
    //Printing a congratulations message
    cout << endl << "GAME " << static_cast<int>(PLAYER.getGame()+1) << " ENDED.";
    cout << endl << "CONGRATULATIONS ";
    getNtfn(PLAYER);             //Call of an function redefined in PStat, that was of Players
    cout << "YOU WON THIS GAME, YOU CONNCTED FOUR TOKENS SUCCESSFULLY!"
         << endl << endl << endl;
}

//____________________________________________________________________________

//Asking user to play more
bool plymore(char *brdptr, const int rows, const int cols)
{
    char input;
    cout << "Would like to play another round?" << endl
         << "Press 1 for Yes OR Press 0 for No." << endl
         << "Your Input: ";
    do{
     cin >> input;
     input = input - 48;
    }while(input != 0 && input != 1);

    //Clearing the board for the next game
    if ( input == 1 )
    {
        for(int index = 0; index < rows*cols; index++)
            *(brdptr + index) = ' ';
        return true;
    }
    else return false;
}

//____________________________________________________________________________

//Checking if board is full
char brdFull(char board[][7], const int cols)
{
    const int topRow = 0;
    char count;
    count = '\0';
    //Checking if the top row is full
    for(int index=0;index<cols;index++) {
        if(board[topRow][index] != ' ')
            count++;
    }
    return count;
}
    
