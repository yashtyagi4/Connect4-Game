/* 
 * Author: Yash Tyagi
 * Created on October 13th, 2020, 9:56 PM
 * Purpose: Connect4 Game
 * Version: 4
 * Description: This version successfully build the game with all it's functionality
 * and a core feature i.e. displaying and saving the leaderboard
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//User Libraries
#include "Ginfo.h"

//Global Constants only
//Math, Physics, Conversions, Higher Order Dimension 

//Function Prototypes
void   rules  ();                                                       //Display Rules
PInfo  *getInfo (int);                                                  //Get Info of Players
PInfo  GetInfo (int);                                                   //Get Info of Players
void   disBrd (char *, const int, const int);                           //Display Board
char   choice (char *, PInfo);                                          //User choice of drop
void   drop   (char [][7], PInfo , const char, const int, int);         //Drop the choice in board
bool   connect(PInfo *, char[][7], const int, const int);               //Check if patterns connects 
void   plyrwon(PInfo *, int, char [][4]);                               //Check if Player won
bool   plymore(char *, const int, const int);                           //Ask players to play more
char   brdFull(char [][7], const int);                                  //Check if board is full
void   lrdrbrd(fstream &,fstream &, PInfo [], int, const int, char []); //Store LeaderBoard in file 
void   showLB(fstream &);                                               //Print Leader Board
void   readStat(fstream &, char, PInfo []);                             //To read and display stats
                                                                        //upto any game


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
    PInfo     players[tplayer];          //Players game play data
    PInfo    *plyrptr[tplayer];          //Array of pointers to players structure
    bool      currwin;                   //Current winner of the present game
    bool      full;                      //To store True if the board is full      
    char      dropPos;                   //Drop position specified by the user
    char      playagn;                   //To store if players want to play again
    int       gameNo;                    //Total number of games
    bool      again;                     //To store the answer if Players wants
                                         //to play another game or not
    string    GStart;                    //To notify the players that the game has started
    fstream   LBFileB;                   //To store Leader Board binary file
    fstream   LBFileT;                   //To store Leader Board txt file
    fstream   allStat;                   //To store all the stats of all games 
    
    
    //To store players stats: 
    //Index 0 : Wins |  Index 1 : Losses | Index 2 : Draws | Index 3 : Moves;
    char stats[tplayer][tstats-1] =  { {'\0','\0','\0','\0'},
                                       {'\0','\0','\0','\0'}};
    
    //Initialize Variables
    currwin = false;
    full = false;
    gameNo = 0;
    GStart = "\0";
    
    //AllStats binary file to show the final updated stats
    allStat.open("AllStats.bin", ios::in | ios:: out | ios:: binary);
    
    //Displaying the rules and instructions of the game
    rules();
    
    //Taking names of the players and assigning them their game ID
    players[P1] = *getInfo(P1);  
    players[P2] =  GetInfo(P2);
    
    //Notify the players that the game has started
    GStart.append(players[P1].name); GStart.append(" and ");
    GStart.append(players[P2].name); GStart.append(", GAME BEGINS! LET'S GO!");
    cout << GStart << endl;

    
    //Displaying the board
    disBrd(brdPtr, brdrows, brdcols);
    do{
        
        again = true;   //Making play again True until specified as False
        
        //Both players turn for 1 time
        for (plyrnum P = P1; P <= P2; P = static_cast<plyrnum>(P+1)) {
            
        //Storing the valid drop position specified in by the player
        dropPos = choice(brdPtr, players[static_cast<int>(P)]);

        //Dropping the Player's Token at the specified position
        drop(board, players[static_cast<int>(P)], dropPos, brdrows, gameNo);
        
        //Displaying the updated board
        disBrd(brdPtr, brdrows, brdcols);

        //Initializing the pointer to the specific player's structure
        plyrptr[P] = &players[P];         

        //Counting total moves in a game
        stats[P][3]++;
        (*(players[P].stats.nmoves + gameNo)) = stats[P][3]; 
        
        
        //Checking if player won
        if( connect(plyrptr[P] ,board, brdrows, brdcols) ) {      
            
                gameNo++;                           //Counting Total Game Numbers 
                plyrwon(plyrptr[P], gameNo, stats); //Counting total wins and losses
                
                
                //Updating the losses 
                (P == P1 ? stats[P2][1]++ : stats[P1][1]++);
                plyrptr[P1]->stats.losses = stats[P1][1];
                plyrptr[P2]->stats.losses = stats[P2][1];
                
                //Updating the total points
                plyrptr[P]->stats.tpoints = plyrptr[P]->stats.tpoints 
                          + (42 - static_cast<int>(stats[P][3]))*10;
                
                
                //Printing the Leader board and saving in files
                lrdrbrd(LBFileB,LBFileT, players, gameNo, tplayer, tmoves);
                
                //Storing all stats in binary file
                for(int plyr=0;plyr<tplayer;plyr++)
                allStat.write(reinterpret_cast<char *>(&(players[plyr].stats)), 
                              sizeof(players[plyr].stats));

                
                //Asking players if they want to play more
                again = plymore(brdPtr, brdrows, brdcols);
                if( again ) {  
                    
                //Making the number of moves 0 for next game
                stats[P1][3] = '\0';
                stats[P2][3] = '\0';
                cout << endl << endl << endl;
                
                //Notifying Players that the game has begin
                cout << GStart << endl;
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

         //Updating the number of draw games
         stats[P1][2]++; stats[P2][2]++;
         plyrptr[P1]->stats.draws = stats[P1][2];
         plyrptr[P2]->stats.draws = stats[P2][2];
         
         //Printing the Leaderboard and saving in files
         lrdrbrd(LBFileB,LBFileT, players, gameNo, tplayer, tmoves );
        
         //Storing the most recent stats in binary file
         for(int plyr=0;plyr<tplayer;plyr++)
            allStat.write(reinterpret_cast<char *>(&(players[plyr].stats)), 
            sizeof(players[plyr].stats));
     }
 
    }while(again);
    
    //Asking user if they want to read stats till any game
    readStat(allStat, gameNo, players);

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
PInfo *getInfo(int P)
{
    PInfo *plyr;
    
    cout << "Player " << (P+1) << " Enter your name: ";
    getline(cin, (plyr)->name);
    (plyr)->plyrID = static_cast<ID>(P);

    return plyr;
}

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
void drop( char board[][7], PInfo plyr, const char dropPos, const int rows, int gameNo)
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

{   //Updating the total wins
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

//Making Leaderboard and saving it in file
void lrdrbrd(fstream &LBFileB, fstream &LBFileT, PInfo players[], int gameNo, const int tPlyrs, char tmoves[])
{
    //LeaderBoard text file to show the final updated stats
    LBFileT.open("Leaderboard.txt", ios::in | ios:: out );
    //LeaderBoard binary file to show the final updated stats
    LBFileB.open("Leaderboard.bin", ios::in | ios:: out | ios:: binary);
 
    //Declaring variables
    const int Size = 70;
    char check, plyr, top;  //top : top player
    
    //Initializing variables
    char Header[Size] = "\t\tLEADERBOARD\nName       Wins  "
                        "Losses   Draws   Moves   Total Points\n";
    check = '\0', plyr='\0', top='\0';
    
    //Making the Leader board in binary file
    for(int plyr=0;plyr<tPlyrs;plyr++)
    LBFileB.write(reinterpret_cast<char *>(&(players[plyr].stats)), sizeof(players[plyr].stats));
    
    //Making the Leader board in txt file
    LBFileT << Header;
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
        LBFileT << left << setw(13) << players[plyr].name
                << right << static_cast<int>(players[plyr].stats.wins) << setw(9)
                << right << static_cast<int>(players[plyr].stats.losses) <<   setw(7)
                << right << static_cast<int>(players[plyr].stats.draws) <<  setw(7)
                << static_cast<int>(tmoves[plyr])
                << setw(13) << right << players[plyr].stats.tpoints << endl;
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
void readStat(fstream& allstat, char gameNo, PInfo players[])
{   
    char input;                 //User specified game
    
    //User Choice
    cout << endl << "Press 1 if you want to read stats till any particular game:";
    cout << endl << "Press 0 if you don't want to read anything and exit: " << endl;
    do{ cin >> input;
      input = input - 48 ;}
    while(input != 1 && input != 0);
    
    if(input == 1){  
        //Variable Declaration
        long cursor1 = 0L;
        long cursor2 = 0L;
        Pstat *ReadP1 = new Pstat;
        Pstat *ReadP2 = new Pstat;
        int game;

        
        do{
        cout << endl << "Upto which game you want to read the stats for?\nEnter a valid number: " << endl;
        cin >> game; 
        }
        while(game < 0 || game ==0 || game > gameNo);

        //Finding the specified game stat cursor for both players
        cursor1 = 2*((game-1)*sizeof(Pstat));
        cursor2 = 2*((game-1)*sizeof(Pstat)) + sizeof(Pstat);

        //Filling the dynamic structure
        allstat.seekg(cursor1,ios::beg);
        allstat.read(reinterpret_cast<char *>(ReadP1),sizeof(Pstat));

        //Printing the stats for Player 1
        cout << endl<< endl;;
        cout << setw(8) << "Name: " << players[0].name << endl;
        cout << setw(8) << "Wins: " << static_cast<int>(ReadP1->wins) << endl
             << setw(8) << "Losses: " << static_cast<int>(ReadP1->losses) << endl
             << setw(8) << "Draws: " << static_cast<int>(ReadP1->draws) << endl
             << setw(8) << "Total Points: " << ReadP1->tpoints << endl;

        allstat.seekg(0L,ios::beg);
        allstat.seekg(cursor2,ios::beg);
        allstat.read(reinterpret_cast<char *>(ReadP2),sizeof(Pstat));    

        //Printing the stats for Player 2
        cout << endl << endl;;
        cout << setw(8) << "Name: " << players[1].name << endl;
        cout << setw(8) << "Wins: " << static_cast<int>(ReadP2->wins) << endl
             << setw(8) << "Losses: " << static_cast<int>(ReadP2->losses) << endl
             << setw(8) << "Draws: " << static_cast<int>(ReadP2->draws) << endl
             << setw(8) << "Total Points: " << ReadP2->tpoints << endl;    

        //Deleting Dynamic Memory
        delete ReadP1;
        delete ReadP2;

        //Closing File
        allstat.close();
    } 
}
