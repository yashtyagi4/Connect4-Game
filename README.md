![Screen Shot 2022-09-11 at 12 35 36 AM](https://user-images.githubusercontent.com/85970478/189514019-5c122650-66a2-4d07-98bd-9ceb312fe97c.png)

#

Connecto is a game in which two players drop discs into a 7 X 6 board. The first player to get four consecutively (either vertically, horizontally, or diagonally) wins. It is a game of strategy. Two players are up against each other to see who can be the first to form a line of 4 of one’s own token.

**Written in C++ with compiler G++ (MinGW.org GCC-6.3.0-1)**

**NetBeans IDE was used with Cygwin-Windows debugger**

# Game Rules

1. It is a two-player game where each player is assigned one of the two tokens/disks: X or O.
2. When the turn will come, each player will drop his/her token into a seven-column, six-row vertically suspended grid.
3. Each player has to drop his/her token in one of column where the piece will fall straight down, occupying the lowest position available.
4. If a column is full, player has to choose another column to drop his/her token.
- Winning condition: The first player to make a consecutive pattern of his/her four tokens, either horizontally, vertically or diagonally, will be the winner.
- Losing condition: If one player made consecutive pattern of his/her four tokens, then another player will lose.
- Draw condition: If the board gets full before any player wins, then the match will be a tie.

# Concepts Used

* Memory allocation with arrays, pointers, structures and Classes.
* Functions with structures and points, used as input and output to the function.
* Pointers with arrays and arrays of structures, utilized both internally as well as externally.
* Utilizing Enum data type, C-string and string variables and memory holders.
* Random access reading and formatted writing to multiple binary and text files simultaneously.
* Utilization of Inherited classes.
* Making the calculations easy with operator overloading
* Using Polymorphism and Aggregation to sort member function according to the requirements.
* Utilization of Templated to reduce the process of making functions for different data types.

# Game Play:

## 1. Rules and Instruction Screen

User will be notified with the rules and instructions at the start of the game.

![image](https://user-images.githubusercontent.com/85970478/188754574-5c50550a-d01e-41fc-a0a7-24dbcda6e89b.png)

## 2. Inputting Player Names

Both the players need to enter their name so that it’s easy for both of the players to know whose turn it is and also their progress can be retrieved easily in the future.

Sample input for Player 1 name: Yash
Sample input for Player 2 name: Jack

![image](https://user-images.githubusercontent.com/85970478/188754667-13c3efab-0f57-4ac4-b8b8-9c954a8115f0.png)

## 3. Game Board

The game board will be displayed at the beginning of every new match and also after each player’s turn.

New Board:

![image](https://user-images.githubusercontent.com/85970478/188754740-55055174-d1ed-45b3-b12c-e4dcb25b11d1.png)

In-Game Board:

![image](https://user-images.githubusercontent.com/85970478/188754768-78079883-ba02-4c8b-ba2b-0593e671348c.png)

## 4. Dropping Tokens
With each turn each player will be asked to choose a valid column index to drop his/her token in the game board.
                                    
![image](https://user-images.githubusercontent.com/85970478/188754894-d1915025-2c4b-4439-8d1a-4affeea900cb.png)

## 5. Winning or Draw Message

After both played enough, probably one of the players will win or the game will end as a draw.

Winning Message:

![image](https://user-images.githubusercontent.com/85970478/188755321-f314304c-8a15-4927-8eec-d7f6841d487f.png)

Draw Message:

![image](https://user-images.githubusercontent.com/85970478/188755348-80f84994-944c-4fdc-9ee0-780b27bd82cb.png)

## 6. Leaderboard

After every match, a leaderboard will be displayed to show the summary of all the matched played.

![image](https://user-images.githubusercontent.com/85970478/188755387-df23ef6b-6e91-4f4c-84f8-6313ae87d1c8.png)

## 7. Playing Another Game

After every match, players will be asked If they want to play more.

Sample Input: 1 (i.e. Yes). In output the new game will begin.

![image](https://user-images.githubusercontent.com/85970478/188755426-f28542e1-0c40-4f3b-b3c2-ce01af2cc253.png)

## 8. Reading Stats Up to a Particular Game

Once players are done with playing with the game, they will be given the functionality to read stats up to any specific match.

Sample Input for option to play another round: 0 (No)
Sample Input for option to read stats up to a particular game: 1 (Yes)
Sample Input for the game to read the stats for: 2

![image](https://user-images.githubusercontent.com/85970478/188755532-87935aee-948e-4209-91f7-747accefaf5c.png)

## 9. Showing Final Leaderboard

Once user sees the stats upto a particular game (if he wanted) then the program also shows a final leaderboard which also have Sum and Difference of the Stats.

![image](https://user-images.githubusercontent.com/85970478/188755610-fc7b552d-49bb-447c-8cc1-7a003a2e7625.png)

## 10. Option to Play with A.I.

Once players are done playing then the program ask the winner of the game to play with the AI.

![image](https://user-images.githubusercontent.com/85970478/188755682-3245d628-b77c-433a-8c2a-c8e5a32aaf3f.png)

## 11. Gameplay with A.I.

Gameplay with AI is same as it was with 2 players. Once someone wins, it will also give the option to ask user to play more.

![image](https://user-images.githubusercontent.com/85970478/188755721-a445c664-4ee4-485d-ac36-58d2e31486dc.png)

# 

# UML Diagram

![UML](https://user-images.githubusercontent.com/85970478/188755865-71f01b3e-62de-4c23-a2c7-f6552bd2c395.png)
