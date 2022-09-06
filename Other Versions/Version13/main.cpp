/* 
 * File:         main.cpp
 * Author:       Yash Tyagi
 * Created :     Dec 4st, 2020, 10:16 PM
 * Purpose:      Connect 4 Game
 * Description:  The purpose of this version is to implement STL functions,
 *               Operator Overloading, Friend class utilization, and other
 *               object-oriented concepts.
 * Version:      13
*/

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

//Defined Files
#include "PInfo.h"
#include "Player.h"
#include "Stat.h"
#include "Data.h"
#include "FInfo.h"

//Global Constants only
//Math, Physics, Conversions, Higher Order Dimension

//Function Prototypes
void   rules  ();                               //Display Rules of the game
Player GetInfo(int);                            //Get the info of the player
//Display the Board after each turn
void   disBrd (char *, const int, const int);
char   choice (char *, Player);                 //Get the Player choice of drop
//Drop the player's choice in board
void   drop   (char [][7], Player , const char, const int); 
//Check if the player's patterns connects
bool   connect(Player *, char[][7], const int, const int);
//Check if Player won, and display the winning message
void   plyrwon(Player *, int, char [][4], Pstat &, Data &, FInfo &); 
bool   plymore(char *, const int, const int);   //Ask players to play more
char   brdFull(char [][7], const int);          //Check if Game board is full  
//Get Info of the player based on the requirement (calls virtual functions)
void   getNtfn(const Player &);
//Display message for the next game (calls virtual function)
void   nextPly(const Stat &);                  
FInfo  getInfo (Player);           //File the basic info for file
//Updating total moves
void   movesIN (int,Pstat &,Pstat &,FInfo [],Data &, Data &,char [][4],char);
void   lossIN  (int,Pstat &,Pstat &,FInfo [],Data &, Data &,char [][4],char);
void   pntsIN  (int,Pstat &,Pstat &,FInfo [],Data &, Data &,char [][4],char,int &,int &);
void   drawIN  (Pstat &,Pstat &,FInfo [],Data &, Data &,char [][4],char);
void   lrdrbrd(fstream &,fstream &, FInfo [], int, const int, char []); //Store LeaderBoard in file 
void   showLB(fstream &);                                               //Print Leader Board
void   readStat(Data ,Data , char, Pstat, Pstat);                       //To read and display stats
                                                                        //upto any game
void   lrbrd(Pstat, Pstat);

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
    FInfo     plyrs[tplayer];            //Player game data to be saved in file
    FInfo    *plyrsptr[tplayer];         //Pointer to player File info
    string    GStart;                    //To notify the players that the game has started
    fstream   LBFileB;                   //To store Leader Board binary file
    fstream   LBFileT;                   //To store Leader Board txt file
    fstream   allStat;                   //To store all the stats of all games 
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
    
    //AllStats binary file to show the final updated stats
    allStat.open("AllStats.bin", ios::in | ios:: out | ios:: binary);
    
    //Displaying the rules and instructions of the game
    rules();
    
    //Taking names of the players and assigning them their game ID
    players[0] = GetInfo(0);
    players[1] = GetInfo(1);
    plyrs[P1] = getInfo(players[P1]);
    plyrs[P2] = getInfo(players[P2]);
    
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
            
        PLAYER1.setGame(static_cast<char>(gameNo));     //Updating games
        
        movesIN(static_cast<int>(P),PLAYER1,PLAYER2,plyrs,PData1,PData2,stats,gameNo);  //Updating moves
        
        //Checking if the player won
        if( connect(plyrptr[P] , board, brdrows, brdcols) ) {   
            
            //Updating the losses
            lossIN(static_cast<int>(P),PLAYER1,PLAYER2,plyrs,PData1,PData2,stats,gameNo);
            
            //Updating the points
            pntsIN(static_cast<int>(P),PLAYER1,PLAYER2,plyrs,PData1,PData2,stats,gameNo,points1,points2);
            
            //Notifying Winner and counting total wins and losses
            if(static_cast<int>(P) == 0)
            plyrwon(plyrptr[P], gameNo, stats, PLAYER1, PData1,plyrs[0]);
            else plyrwon(plyrptr[P], gameNo, stats, PLAYER2, PData2,plyrs[1]);
            
            gameNo++;
            
            //Printing the Leader board and saving in files
            lrdrbrd(LBFileB,LBFileT, plyrs, gameNo, tplayer, tmoves);
            
            //Storing all stats in binary file
            for(int plyr=0;plyr<tplayer;plyr++)
            allStat.write(reinterpret_cast<char *>(&(plyrs[plyr])), 
            sizeof(plyrs[plyr]));
            
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
         
         LBFileB.open("Leaderboard.bin", ios::in | ios:: out | ios:: binary);
         LBFileT.open("Leaderboard.txt", ios::in | ios:: out );
         
         gameNo++;              //Counting Total Game Numbers
         
         cout << "THE BOARD IS FULL, IT IS A DRAW!" << endl;
         again = plymore(brdPtr, brdrows, brdcols); 
 
         //Displaying the Board
         if(again == true) disBrd(brdPtr, brdrows, brdcols);
         
         drawIN(PLAYER1,PLAYER2,plyrs,PData1,PData2,stats,gameNo);      //Updating the draws
         
         lrdrbrd(LBFileB,LBFileT, plyrs, gameNo, tplayer, tmoves );     //Printing Leaderboard, saving in files
        
         //Storing the most recent stats in binary file
         for(int plyr=0;plyr<tplayer;plyr++)
            allStat.write(reinterpret_cast<char *>(&(plyrs[plyr])), 
            sizeof(plyrs[plyr]));
         
         gameNo++;
     }
  
    }while(again);
    
    //Utilizing copy constructor
    Pstat PLYR1 = PLAYER1;
    Pstat PLYR2 = PLAYER2;
    Data  PD1   = PData1;
    Data  PD2   = PData2;
    
    //Asking user if they want to read stats till any game
    readStat(PD1,PD2,gameNo,PLYR1,PLYR2);
    
    //Print the final leaderboard
    lrbrd(PLYR1,PLYR2);
    
    
    //Deleting the dynamic memories of File Info(FInfo)
    delete plyrs[P1].nmoves;
    delete plyrs[P2].nmoves;
    
    //Exit Stage Right
    cout << endl << "Thank you for playing!" << endl;
    return 0;
}

//__________________________________________________________________________

//Printing the leaderboard
void lrbrd(Pstat Plyr1, Pstat Plyr2){
    for(int i=0;i<25;i++)
        cout << "-";
    cout << "FINAL LEADERBOARD";
    for(int i=0;i<25;i++)
        cout << "-";
    cout << endl;
    //Player 1
    cout << "NAME" << setw(10) << "ID" << setw(10) << "WINS" << setw(10)
         << "LOSSES" << setw(10) << "DRAWS" << setw(10) << "MOVES" << setw(10) << "POINTS" << endl;
    cout << Plyr1.getName() << right << setw(10);
    if ( Plyr1.getID() == 0 ) cout << "X";
    else cout << "O";
    cout << setw(10) << static_cast<int>(Plyr1.getWins()) << setw(10) 
         << static_cast<int>(Plyr1.getLoss()) << setw(10) << static_cast<int>(Plyr1.getDraw())
         << setw(10) << static_cast<int>(Plyr1.getMoves()) << setw(10) << Plyr1.getPnts() << endl;
    //Player 2
    cout << Plyr2.getName() << right << setw(10);
    if ( Plyr2.getID() == 1 ) cout << "O";
    else cout << "X";
    cout << setw(10) << static_cast<int>(Plyr2.getWins()) << setw(10) 
         << static_cast<int>(Plyr2.getLoss()) << setw(10) << static_cast<int>(Plyr2.getDraw())
         << setw(10) << static_cast<int>(Plyr2.getMoves()) << setw(10) << Plyr2.getPnts() << endl;
    
    Pstat Sum, Diff;      //Stat Difference and Sun
    
    //Using overloaded operator to fine stats sum and difference
    Sum  = Plyr1.operator +(Plyr2);
    Diff = Plyr1.operator -(Plyr2);
    cout << "SUM: " <<  setw(9)  << static_cast<int>(Sum.getWins()) << setw(10) 
         << static_cast<int>(Sum.getLoss()) << setw(10) <<  static_cast<int>(Sum.getDraw()) 
         << setw(20) << static_cast<int>(Sum.getMoves()) << setw(10) << Sum.getPnts() << endl;
    cout << "DIFF:" <<  setw(9) << static_cast<int>(Diff.getWins()) << setw(10) 
         << static_cast<int>(Diff.getLoss()) << setw(10) << static_cast<int>(Diff.getDraw()) 
         << setw(20) << static_cast<int>(Diff.getMoves()) << setw(10) 
         << Diff.getPnts() << endl;
}

//__________________________________________________________________________
//Updating the number of draw games
void drawIN(Pstat &PLAYER1,Pstat &PLAYER2,FInfo plyrs[],Data &PData1, Data &PData2
            ,char stats[][4],char gameNo){
    
    stats[0][2]++; stats[1][2]++;
    PLAYER1.setDraw(stats[0][2]);
    plyrs[0].draws = stats[0][2];
    plyrs[1].draws = stats[1][2];

    PData1.fillTDraw(PLAYER1,gameNo);
    PData2.fillTDraw(PLAYER2,gameNo);
}

//__________________________________________________________________________

//Updating points
void pntsIN(int P,Pstat &PLAYER1,Pstat &PLAYER2,FInfo plyrs[],Data &PData1, Data &PData2
            ,char stats[][4],char gameNo, int &points1, int &points2){
    
    if(static_cast<int>(P) == 0){
        points1 = points1 + (42 - static_cast<int>(stats[P][3]))*10;
        PLAYER1.setPnts(points1);
        PData1.fillTPnts(PLAYER1,gameNo);
    }
    else {
        points2 = points2 + (42 - static_cast<int>(stats[P][3]))*10;
        PLAYER2.setPnts(points2);
        PData2.fillTPnts(PLAYER1,gameNo);  
    }
    plyrs[P].tpoints = plyrs[P].tpoints + (42 - static_cast<int>(stats[P][3]))*10;

}

//__________________________________________________________________________

//Updating moves
void movesIN(int P,Pstat &PLAYER1,Pstat &PLAYER2,FInfo plyrs[],Data &PData1, Data &PData2
            ,char stats[][4],char gameNo){
    
    //Counting moves of the player for the game
    stats[P][3]++;
    if(P == 0)
         PLAYER1.setMove(stats[P][3]);
    else PLAYER2.setMove(stats[P][3]);
    (*(plyrs[P].nmoves + gameNo )) = stats[P][3];
    
    //Filling the moves of this game in Player's data
    if(P == 0)
    PData1.fillTMovs(PLAYER1,gameNo);
    else PData2.fillTMovs(PLAYER2,gameNo);
}

//__________________________________________________________________________

//Updating loss
void lossIN(int P,Pstat &PLAYER1,Pstat &PLAYER2,FInfo plyrs[],Data &PData1, Data &PData2
            ,char stats[][4],char gameNo){
    //Updating the losses
    ( static_cast<int>(P) == 0 ? stats[P+1][1]++ : stats[P][1]++ );
    PLAYER1.setLoss(stats[P][1]);
    PLAYER2.setLoss(stats[P+1][1]);
    plyrs[P].losses = stats[P][1];
    plyrs[P+1].losses = stats[P+1][1];

    //Filling the losses of this game in Player's data
    if(static_cast<int>(P) == 0)
    PData2.fillTLoss(PLAYER2,gameNo);
    else PData1.fillTLoss(PLAYER1,gameNo);
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
    bool      again;
   
    do{
    again = false;
    if(P == 0)
    cout << "Player 1 Enter your name: ";
    else cout << "Player 2 Enter your name: ";
    try{
    getline(cin, name, '\n');
    plyr.setName(name);
    }
    catch(Player::InvldNm){
        cout << endl << "ERROR! You didn't enter a name. Type Again!" << endl;
        again = true;
    }
    }while(again == true);
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
    bool again;
    
    do{
        again = false;
        try{
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
        if(index < 0 || index > 6)
            throw -1;
        }
        catch (int){
            cout << endl << "ERROR! You entered a index out of reach." << endl;
            again = true;
        }
    }while(again);
    
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
void plyrwon(Player *plyrptr, int gameNo, char stats[][4], Pstat &PLAYER, Data &PData, FInfo &plr)
{   
    //Updating the total wins
    if(plyrptr->getID() == 0){
        stats[0][0]++;
        PLAYER.setWins(stats[0][0]);
        plr.wins = stats[0][0];
    }
    else {
        stats[1][0]++;
        PLAYER.setWins(stats[1][0]);
        plr.wins = stats[1][0];
    }
    PData.fillTWins(PLAYER,gameNo);     //Filling the wins of of the player for this game
    
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
    bool again;
    
    do{
    again = false;
    try{
    cout << "Would like to play another round?" << endl
         << "Press 1 for Yes OR Press 0 for No." << endl
         << "Your Input: ";
     cin >> input;
     input = input - 48;
     if(input !=0 && input != 1)
         throw -1;
    }
    catch (int){
        cout << endl << "Error! You entered a wrong integer. Please enter a valid input." << endl;
        again = true;
    }
    }while(again);

    
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
    
//Taking names of the players and assigning them their game ID
FInfo getInfo(Player player)
{
    FInfo plyr;
    plyr.name = player.getName();
    plyr.plyrID = player.getID();

    return plyr;
}


//____________________________________________________________________________

//Making Leaderboard and saving it in file
void lrdrbrd(fstream &LBFileB, fstream &LBFileT, FInfo players[], int gameNo, const int tPlyrs, char tmoves[])
{
    //LeaderBoard text file to show the final updated stats
    LBFileT.open("Leaderboard.txt", ios::in | ios:: out );
    //LeaderBoard binary file to show the final updated stats
    LBFileB.open("Leaderboard.bin", ios::in | ios:: out | ios:: binary);
 
    //Declaring variables
    const int Size = 70;
    char check, plyr, top;  //top : top player
    int pnts1, pnts2;
    
    //Initializing variables
    char Header[Size] = "\t\tLEADERBOARD\nName       Wins  "
                        "Losses   Draws   Moves   Total Points\n";
    check = '\0', plyr='\0', top='\0'; pnts1 = 0; pnts2;
    
    //Storing the points from file info structure players
    pnts1 = players[static_cast<int>(plyr)].tpoints;
    pnts2 = players[static_cast<int>(plyr+1)].tpoints;
    
    //Making the Leader board in binary file
    for(int plyr=0;plyr<tPlyrs;plyr++)
    LBFileB.write(reinterpret_cast<char *>(&(players[plyr])), sizeof(players[plyr]));
    
    //Making the Leader board in txt file
    LBFileT << Header;
    while(true)
    {
        if(static_cast<int>(check)==tPlyrs) break;    //Check for iteration only for total players
        
        //Checking who has more points and then printing in file accordingly
        if(static_cast<int>(check)==0){
        if( max(pnts1,pnts2) == pnts1 )
        {   plyr = 0; top = 1; } 
        else { plyr = 1; top = -1;}
        }
        
        tmoves[plyr] = tmoves[plyr] + (*players[plyr].nmoves + (gameNo-1));
        LBFileT << left << setw(13) << players[plyr].name
                << right << static_cast<int>(players[plyr].wins) << setw(9)
                << right << static_cast<int>(players[plyr].losses) <<   setw(7)
                << right << static_cast<int>(players[plyr].draws) <<  setw(7)
                << static_cast<int>(tmoves[plyr])
                << setw(13) << right << players[plyr].tpoints << endl;
        plyr = static_cast<char>(plyr+top);
        check++;
    }
    
    //Resetting the cursor
    LBFileT.seekp(0L, ios:: beg);
    LBFileB.seekp(0L, ios:: beg);
    
    //Printing the Leader board
    showLB(LBFileT);
     
    //Closing the Txt File
    LBFileT.close();
    LBFileB.close();
}

//____________________________________________________________________________

//Displaying the cursor
void showLB(fstream &LBFileT)
{
    string line;
    
    for(int i=0;i<4;i++){
        getline(LBFileT, line, '\n');
        cout << line << endl;
    } 
    cout << endl << endl << endl;
}

//____________________________________________________________________________

//Reading and displaying the stats upto the players specified game
void readStat(Data PData1,Data PData2, char gameNo, Pstat PLAYER1, Pstat PLAYER2)
{   
    char input;                 //User specified game
    bool again;
    
    do{ 
    again = false;
    try{
    //User Choice
    cout << endl << "Press 1 if you want to read stats till any particular game:";
    cout << endl << "Press 0 if you don't want to read anything and exit: " << endl;
    
    cin >> input;
    input = input - 48 ;
    if(input != 1 && input != 0)
        throw -1;
    }
    catch (int){
        cout << endl << "Error! You entered a wrong input." << endl;
        again = true;
    }
    }
    while(again);
    
    if(input == 1){  
        //Variable Declaration
        int game;
        
        do{
        again = false;
        try{
        cout << endl << "Upto which game you want to read the stats for?"
                        "\nEnter a valid number: " << endl;
        cin >> game; 
        if(game < 0 || game == 0 || game > gameNo )
            throw -1;
        }
        catch(int){
            cout << "Error! You Entered a game that doesn't exist. Enter again." << endl;
            again = true;
        } 
        }
        while(game < 0 || game == 0 || game > gameNo);

        //Printing the stats for Player 1
        cout << endl<< endl;;
        cout << setw(8) << "Name: " << PLAYER1.getName() << endl;
        cout << setw(8) << "ID: " << (PLAYER1.getID()==0?"X":"O") << endl;
        cout << setw(8) << "Wins: " << static_cast<int>(PData1.getTWins(game-1)) << endl
             << setw(8) << "Losses: " << static_cast<int>(PData1.getTLoss(game-1)) << endl
             << setw(8) << "Draws: " << static_cast<int>(PData1.getTDraw(game-1)) << endl
             << setw(8) << "Moves: " << static_cast<int>(PData1.getTMovs(game-1)) << endl
             << setw(8) << "Total Points: " << static_cast<int>(PData1.getTPnts(game-1)) << endl;
        
        //Printing the stats for Player 1
        cout << endl << endl;;
        cout << setw(8) << "Name: " << PLAYER2.getName() << endl;
        cout << setw(8) << "ID: " << (PLAYER2.getID()==0?"X":"O") << endl;
        cout << setw(8) << "Wins: " << static_cast<int>(PData2.getTWins(game-1)) << endl
             << setw(8) << "Losses: " << static_cast<int>(PData2.getTLoss(game-1)) << endl
             << setw(8) << "Draws: " << static_cast<int>(PData2.getTDraw(game-1)) << endl
             << setw(8) << "Moves: " << static_cast<int>(PData2.getTMovs(game-1)) << endl
             << setw(8) << "Total Points: " << static_cast<int>(PData2.getTPnts(game-1)) << endl;

    } 
}