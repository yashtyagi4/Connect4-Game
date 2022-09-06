/* 
 * Author: Yash Tyagi
 * Created on October 7th, 2020, 2:56 PM
 * Purpose: Connect4 game
 * Version: 1
 * Description: This version focuses on just game development and functioning
 */

//System Libraries
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//User Libraries
struct PInfo{   
    string name;                    //Name of the player
    char plyrID;                    //Player ID/Token in the game
};

//Global Constants only
//Math, Physics, Conversions, Higher Order Dimension 

//Function Prototypes
void   disBrd (char *, const int, const int);                           //Display Board
char   choice (char *, PInfo);                                          //User choice of drop
void   drop   (char [][7], PInfo , const char, const int);              //Drop the choice in board
bool   connect(PInfo *, char[][7], const int, const int);               //Check if patterns connects 
void   plyrwon(PInfo *);                                                //Check if Player won
bool   plymore(char *, const int, const int);                           //Ask players to play more
char   brdFull(char [][7], const int);                                  //Check if board is full

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare all variables 
    const int tplayer = 2;               //Total number of players
    const int brdrows = 6;               //Number of rows in the board
    const int brdcols = 7;               //Number of columns in the board
    char      board[brdrows][brdcols];   //Game Board 2-D grid
    char     *brdPtr = (char*)board;     //Pointer to board array
    PInfo     players[tplayer];          //Players game play data
    PInfo    *plyrptr[tplayer];          //Array of pointers to players structure
    char      dropPos;                   //Drop position specified by the user
    char      playagn;                   //To store if players want to play again
    bool      again;                     //To store the answer if Players wants
                                         //to play another game or not
    
    //Taking names of the players and assigning them their game ID
    cout << "Player 1 Enter your name: ";
    getline(cin, players[0].name);
    players[0].plyrID = 'X';
    cout << "Player 2 Enter your name: ";
    getline(cin, players[1].name);
    players[1].plyrID = 'O';

    //Displaying the board
    disBrd(brdPtr, brdrows, brdcols);
    
    do{ again = true;   //Making play again True until specified as False
        
        //Both players turn for 1 time
        for (int P = 0; P <= 1; P++) {
        //Storing the valid drop position specified in by the player
        dropPos = choice(brdPtr, players[P]);

        //Dropping the Player's Token at the specified position
        drop(board, players[P], dropPos, brdrows);
        
        //Displaying the updated board
        disBrd(brdPtr, brdrows, brdcols);

        //Initializing the pointer to the specific player's structure
        plyrptr[P] = &players[P];         
        
        //Checking if player won
        if( connect(plyrptr[P] , board, brdrows, brdcols) ) {      
                plyrwon(plyrptr[P]);                        //Notifying Winner
                
                //Asking players if they want to play more
                again = plymore(brdPtr, brdrows, brdcols);
                if( again ) {  
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
        if(plyr.plyrID == 'X') cout << "X" << endl; else cout << "O" << endl;
        
        
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
                    board[row][static_cast<int>(dropPos)] = (plyr.plyrID == 'X'? 'X' : 'O');
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
    
    if(plyrptr->plyrID == 'X') token = 'X';
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
void plyrwon(PInfo *plyrptr)

{   
    //Printing a congratulations message
    cout << endl << "CONGRATULATIONS " << plyrptr->name << "!" << endl 
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