/* 
 * Author: Yash Tyagi
 * Created on October 9th, 2020, 5:12 PM
 * Purpose: Connect4 Game
 * Version: 2
 * Description: This version focuses on effectivity building Structures and 
 * their functionality over the version 1 code
 */

//System Libraries
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//User Libraries
#include "GInfo.h"

//Global Constants only
//Math, Physics, Conversions, Higher Order Dimension 

//Function Prototypes
void   rules ();                                                        //To Display rules
PInfo  GetInfo(int);                                                    //To take user inputs 
void   disBrd (char *, const int, const int);                           //Display Board
char   choice (char *, PInfo);                                          //User choice of drop
void   drop   (char [][7], PInfo , const char, const int);              //Drop the choice in board
bool   connect(PInfo *, char[][7], const int, const int);               //Check if patterns connects 
void   plyrwon(PInfo *, int, char [][4]);                                                //Check if Player won
bool   plymore(char *, const int, const int);                           //Ask players to play more
char   brdFull(char [][7], const int);                                  //Check if board is full                                                                       //upto any game
void   lrdrbrd(PInfo [], int, const int, char []);                      //To print the leaderboard

//Execution Begins Here
int main(int argc, char** argv) {
    enum plyrnum { P1 , P2 };
    
    //Declare all variables 
    const int tplayer = 2;               //Total number of players
    const int brdrows = 6;               //Number of rows in the board
    const int brdcols = 7;               //Number of columns in the board
    const int tstats = 5;                //To store total stats of a Player
    char      tmoves[tplayer];           //Total number of moves by each player
    char      board[brdrows][brdcols];   //Game Board 2-D grid
    char     *brdPtr = (char*)board;     //Pointer to board array
    PInfo     players[tplayer];          //Players game play data
    PInfo    *plyrptr[tplayer];          //Array of pointers to players structure
    char      dropPos;                   //Drop position specified by the user
    char      playagn;                   //To store if players want to play again
    int       gameNo;                    //Total number of games
    bool      again;                     //To store the answer if Players wants
                                         //to play another game or not

    //To store players stats: 
    //Index 0 : Wins |  Index 1 : Losses | Index 2 : Draws | Index 3 : Moves;
    char stats[tplayer][tstats-1] =  { {'\0','\0','\0','\0'},
                                       {'\0','\0','\0','\0'}};
    
    //Initialize Variables
    gameNo = 0;
    
    //Displaying the rules
    rules();
    
    //Taking names of the players and assigning them their game ID
    players[P1] =  GetInfo(P1);
    players[P2] =  GetInfo(P2);
    
    
    //Displaying the board
    disBrd(brdPtr, brdrows, brdcols);
    
    do{ again = true;   //Making play again True until specified as False
        
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
        
        //Counting total moves in a game
        stats[P][3]++;
        (*(players[P].stats.nmoves + gameNo)) = stats[P][3]; 
        
        //Checking if player won
        if( connect(plyrptr[P] , board, brdrows, brdcols) ) {   
                gameNo++;                              //Counting total games
                plyrwon(plyrptr[static_cast<int>(P)],gameNo,stats); //Notifying Winner
                
                //Updating the losses
                (P == P1 ? stats[P2][1]++ : stats[P1][1]++);
                plyrptr[P1]->stats.losses = stats[P1][1];
                plyrptr[P2]->stats.losses = stats[P2][1];
                
                //Updating the total points
                plyrptr[P]->stats.tpoints = plyrptr[P]->stats.tpoints 
                          + (42 - static_cast<int>(stats[P][3]))*10;
                
                //Printing the Leader board
                lrdrbrd(players, gameNo, tplayer,tmoves);
                
                //Asking players if they want to play more
                again = plymore(brdPtr, brdrows, brdcols);
                if( again ) { 
                    
                //Making the number of moves 0 for next game
                stats[P1][3] = '\0';
                stats[P2][3] = '\0';
                cout << endl << endl << endl;
                    
                disBrd(brdPtr, brdrows, brdcols);         //Displaying the Board
                break; }
                else break;
        }  
    }

     //Checking if the board is full
     if( static_cast<int>( brdFull(board, brdcols) ) == 7 ){
         
         gameNo++;                  //Counting Total Game Numbers
         
         cout << "THE BOARD IS FULL, IT IS A DRAW!" << endl;
         again = plymore(brdPtr, brdrows, brdcols);
         
         //Displaying the Board
         if(again == true) disBrd(brdPtr, brdrows, brdcols);
         
         //Updating the number of draw games
         stats[P1][2]++; stats[P2][2]++;
         plyrptr[P1]->stats.draws = stats[P1][2];
         plyrptr[P2]->stats.draws = stats[P2][2];
         
         //Printing the leaderboard
         lrdrbrd(players, gameNo, tplayer, tmoves);
         
     }
    }while(again);
    
    //Deleting the dynamic memories
    delete players[P1].stats.nmoves;
    delete players[P2].stats.nmoves;
    
    //Exit Stage Right
    cout << endl << "Thank you for playing!" << endl;
    return 0;
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
PInfo GetInfo(int P)
{
    PInfo plyr;
    
    cout << "Player " << (P+1) << " Enter your name: ";
    getline(cin, plyr.name);
    plyr.plyrID = static_cast<ID>(P);

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
char choice( char *brdPtr, PInfo plyr ){
    char index;
    
    do{
        cout << plyr.name << "'s Turn! Your token is: ";
        if(plyr.plyrID == 0) cout << "X" << endl; else cout << "O" << endl;
        
        
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
void drop( char board[][7], PInfo plyr, const char dropPos, const int rows)
{
	int row = rows-1;
        bool done;
	done = false;

	do 
	{
            if ( board[row][static_cast<int>(dropPos)] != 'X' 
              && board[row][static_cast<int>(dropPos)] != 'O' )
            {
                    board[row][static_cast<int>(dropPos)] = (plyr.plyrID == 0? 'X' : 'O');
                    done = true;
            }
		else (--row);
	} while( done != true );
}

//__________________________________________________________________________

//Checking if connection was made or not
bool connect(PInfo *plyrptr, char board[][7], const int rows, const int cols)
{
    char token;                     //Player ID
    bool win;                       //To store the result if player won or not
    
    if(plyrptr->plyrID == 0) token = 'X';
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
void plyrwon(PInfo *plyrptr, int gameNo, char stats[][4])
{   
    //Updating the total wins
    if(plyrptr->plyrID == 0) {stats[0][0]++; plyrptr->stats.wins = stats[0][0];}
    else { stats[1][0]++;  plyrptr->stats.wins = stats[1][0]; }
    
    //Printing a congratulations message
    cout << endl << "GAME " << static_cast<int>(gameNo) << " ENDED."
         << endl << "CONGRATULATIONS " << plyrptr->name << "!" << endl 
         << "YOU WON THIS GAME, YOU CONNCTED FOUR TOKENS SUCCESSFULLY!"
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


//____________________________________________________________________________

//Printing the leaderboard
void lrdrbrd(PInfo players[], int gameNo, const int tPlyrs, char tmoves[])
{
    //Declaring variables
    char check, plyr, top; //top : top player
    
    //Initialize variables
    check = '\0', plyr='\0', top='\0';
    
    cout << "\t\tLEADERBOARD\nName       Wins  "
              "Losses   Draws   Moves   Total Points\n";
    
    while(true)
    {
        if(static_cast<int>(check)==tPlyrs) break;    //Check for iteration only for total players
        
        //Checking who has more points and then printing in file accordingly
        if(static_cast<int>(check)==0){
        if( (players[static_cast<int>(plyr)].stats.tpoints >= 
                players[static_cast<int>(plyr+1)].stats.tpoints) )
        {plyr = 0; top = 1; } 
        else { plyr = 1; top = -1;}
        }
        
        tmoves[plyr] = tmoves[plyr] + (*players[plyr].stats.nmoves + (gameNo-1));
        cout << left << setw(13) << players[plyr].name
                << right << static_cast<int>(players[plyr].stats.wins) << setw(9)
                << right << static_cast<int>(players[plyr].stats.losses) <<   setw(7)
                << right << static_cast<int>(players[plyr].stats.draws) <<  setw(7)
                << static_cast<int>(tmoves[plyr])
                << setw(13) << right << players[plyr].stats.tpoints << endl;
        plyr = static_cast<char>(plyr+top);
        check++;
    }
}