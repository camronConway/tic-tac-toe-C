/*
* Project 5 Camron Conway
*
* Description: This program simulates a game of tic tac toe. The player is asked
* to pick X or O. This program recognizes both lower and upper case. The computer is
* assigned the opposite of whatever the user chooses. Whichever player is X goes first it
* choosing a number on the board. The computer makes its choice first by picking an available space
* that it can win on. If it cannot win the computer will then choose a space that will block the player
* from winning. If neither option is available the computer will choose a random space available
* from 1-9. The game will end win a player wins or at the end of 9 turns which would result in a draw.
*
* Input: The user is first prompted to pick a letter of their choosing (X or O).
* Then on each turn the player is asked to pick a number representing a space on
* the board.
*
* Output: A three by three board of numbers from 1-9 is printed on the screen.
* Each time the player or computer picks a number it is replaced with and X or O respectively.
* A winning message is printed at the end of the game, if the player wins, or if the computer wins
* or if there is a draw.
*
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

#define FLUSH while(getchar()!= '\n')

void printBoard(char gameArray[3][3]);
char userChoice(void);
void playerTurn(char gameArray[3][3], char playerXO);
void computerTurn(char gameArray[3][3], char compXO, char playerXO);
int checkWin(char gameArray[3][3], char win);
int computerBlock(char gameArray[3][3], char playerXO);

int main (void)
{
    //arrayDeclaration
    char gameBoard [3][3] = {
                             {'1', '2' , '3'},
                             {'4', '5', '6'},
                             {'7', '8', '9'}
                            };
    //local declarations
    char playerXO;
    char compXO;
    int numTurns = 0;
    int winCountP = 0;
    int winCountC = 0;
    //seed random number generator
    srand(time(NULL));

    //Title/author
    printf("\nProject 5 COP2220 - Camron Conway\n");
    //Game Greeting
    printf("\nLet's play TIC-TAC-TOE!\n");
    //prompt for player
    playerXO = userChoice();
    //chooses computers letter based on player decision
    if(playerXO == 'X')
    {
        compXO = 'O';
    }
    else
        compXO = 'X';

    printBoard(gameBoard);
    //start of the game
    while(numTurns < 9)
    {
        if(playerXO == 'X')//player goes first
        {
            playerTurn(gameBoard, playerXO);
            winCountP = checkWin(gameBoard, playerXO);
            if(winCountP > 0)
            {
                printf("\nYou win!");
                break;
            }
            numTurns++;
            if(numTurns == 9)break;
            computerTurn(gameBoard, compXO, playerXO);
            winCountC = checkWin(gameBoard, compXO);
            if(winCountC > 0)
            {
                printf("Sorry you lose.");
                break;
            }
            numTurns++;
            printBoard(gameBoard);
        }
        else//player goes second
        {
            computerTurn(gameBoard, compXO, playerXO);
            winCountC = checkWin(gameBoard, compXO);
            if(winCountC > 0)
            {
                printf("Sorry you lose.");
                break;
            }
            numTurns++;
            if(numTurns == 9)break;
            printBoard(gameBoard);
            playerTurn(gameBoard, playerXO);
            winCountP = checkWin(gameBoard, playerXO);
            if(winCountP > 0)
            {
                printf("\nYou win!");
                break;
            }
            numTurns++;
        }
    }//while
    if(numTurns == 9)//no one wins
    {
        printf("\nThe game is a draw");
    }
    printBoard(gameBoard);

    return 0;
}

/*
* Function Name: printBoard
*
* Parameters: a character array that is 3x3
*
* Return type: void
*
* Description: This function prints a character array 3x3 in a way that
* simulates a tic tac toe game board.
*
*/
void printBoard(char gameBoard[3][3])
{
    printf("\n    %c | %c | %c", gameBoard[0][0], gameBoard[0][1], gameBoard[0][2]);
    printf("\n  ----+---+----");
    printf("\n    %c | %c | %c", gameBoard[1][0], gameBoard[1][1], gameBoard[1][2]);
    printf("\n  ----+---+----");
    printf("\n    %c | %c | %c", gameBoard[2][0], gameBoard[2][1], gameBoard[2][2]);
    printf("\n");

    return ;
}
/*
* Function name: userChoice
*
* Parameters: none
*
* Return type: char value
*
* Description: This function prompts the user to choose X or O.
* The function takes the input the user gives an turns it into the uppercase variant
* so that by this it can recognize both 'x' and 'o' as well. The prompt is repeated if
* the user's input is invalid. Also the function will end the program if EOF is entered.
* The function returns the user's valid choice back to the main function.
*/
char userChoice(void)
{
    char playerChoice;

    printf("Do you want to be X or O (X goes first)?: ");
    int gameChoice = scanf("%c", &playerChoice);
    playerChoice = toupper(playerChoice);


    while(playerChoice != 'X' && playerChoice != 'O' && gameChoice != EOF)
       {
           FLUSH;
           printf("Do you want to play as X or O (X goes first): ");
           gameChoice = scanf("%c", &playerChoice);

           playerChoice = toupper(playerChoice);
       }//while

    if(gameChoice == EOF)
    {
        printf("No choice made exiting the game.");
        exit(101);
    }
    return playerChoice;
}

/*
* Function name: playerTurn
*
* Parameters: character array 3x3, character value representing the current player (X or O)
*
* Return type: void
*
* Description: This function prompts the user to make a choice 1-9 that represents an available space on the board.
* The prompt is repeated until a valid number is picked. Once the choice is valid it is put into two calculations
* that will give the row and column space on the array.
*/
void playerTurn(char gameArray[3][3], char playerXO)
{
   //local declarations
   int playerSelect = 0;
   int playerSelCheck;
   int validSpace = 0;

   //prompt
   printf("\nEnter the number of an available space, you are %c: ", playerXO);
   playerSelCheck = scanf("%d", &playerSelect);
   //check
   while(validSpace != 1 && playerSelCheck != EOF)
   {
       while((playerSelCheck != 1) && (playerSelCheck != EOF))
        {
            FLUSH;
            printf("\nWhat space would you like to take?: ");
            playerSelCheck = scanf("%d", &playerSelect);
        }
       while((playerSelect < 0) || (playerSelect > 9))
        {
            FLUSH;
            printf("\nWhat space would you like to take?: ");
            playerSelCheck = scanf("%d", &playerSelect);
        }
       //game board changes
       int row = (playerSelect - 1)/3;
       int col = ((playerSelect - 1)%3);

       if(gameArray[row][col] != 'X' && gameArray[row][col] != 'O')
       {
           gameArray[row][col] = playerXO;
           validSpace = 1;
       }//if
       else
       {
           FLUSH;
           printf("\nWhat space would you like to take?: ");
           playerSelCheck = scanf("%d", &playerSelect);
       }

   }//while

   if(playerSelCheck == EOF)
        {
            printf("Exit entered, exiting");
            exit(102);
        }//if

    return ;
}
/*
* Function name: computerTurn
*
* Parameters: character array 3x3, character value representing the computer X or O, character value representing the computer X or O
*
* Return type: void
*
* Description: This function is the computer's "brain". The computer checks to see if there is a spot on the board where it can win.
* If not it then checks for a spot on the board where it can block the player from winning. If neither option is valid it then chooses a random
* spot available on the board.
*/
void computerTurn(char gameArray[3][3], char compXO, char playerXO)
{
    int compValid = 0;
    int compChoice = 0;
    int winMove = 0;

    //check win space 1
    if(gameArray[0][0] == '1' && gameArray[0][1] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    if(gameArray[0][0] == '1' && gameArray[1][1] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    if(gameArray[0][0] == '1' && gameArray[1][0] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    //check win space 2
    if(gameArray[0][1] == '2' && gameArray[0][0] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 2;
        compValid = 1;
    }
    if(gameArray[0][1] == '2' && gameArray[1][1] == compXO && gameArray[2][1] == compXO)
    {
        compChoice = 2;
        compValid = 1;
    }
    //check win space 3
    if(gameArray[0][2] == '3' && gameArray[0][1] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    if(gameArray[0][2] == '3' && gameArray[1][2] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    if(gameArray[0][2] == '3' && gameArray[1][1] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    //check win space 4
    if(gameArray[1][0] == '4' && gameArray[1][1] == compXO && gameArray[1][2] == compXO)
    {
        compChoice = 4;
        compValid = 1;
    }
    if(gameArray[1][0] == '4' && gameArray[0][0] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 4;
        compValid = 1;
    }
    //check win space 5
    if(gameArray[1][1] == '5' && gameArray[1][0] == compXO && gameArray[1][2] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[0][1] == compXO && gameArray[2][1] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[0][0] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[1][2] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    //check win space 6
    if(gameArray[1][2] == '6' && gameArray[1][1] == compXO && gameArray[1][0] == compXO)
    {
        compChoice = 6;
        compValid = 1;
    }
    if(gameArray[1][2] == '6' && gameArray[0][2] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 6;
        compValid = 1;
    }
    //check win space 7
    if(gameArray[2][0] == '7' && gameArray[2][1] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    if(gameArray[2][0] == '7' && gameArray[1][0] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    if(gameArray[2][0] == '7' && gameArray[1][1] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    //check win space 8
    if(gameArray[2][1] == '8' && gameArray[2][0] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 8;
        compValid = 1;
    }
    if(gameArray[2][1] == '8' && gameArray[1][1] == compXO && gameArray[0][1] == compXO)
    {
        compChoice = 8;
        compValid = 1;
    }
    //check win space 9
    if(gameArray[2][2] == '9' && gameArray[2][1] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }
    if(gameArray[2][2] == '9' && gameArray[1][2] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }
    if(gameArray[2][2] == '9' && gameArray[1][1] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }


    //Takes the win if available
    if(compValid == 1)
    {
    int row = (compChoice - 1)/3;
    int col = (compChoice - 1)%3;
    gameArray[row][col] = compXO;
    winMove++;
    printf("\nThe computer went for the win on space: %d\n", compChoice);
    }
    //checks to see if computer can block player
    int blockPlayer = computerBlock(gameArray, playerXO);
    if(blockPlayer > 0 && compValid != 1)
    {
        compChoice = blockPlayer;
        compValid = 1;
    }
    //the computer goes for the block if it cannot win
    if(compValid == 1 && winMove == 0)
    {
    int row = (compChoice - 1)/3;
    int col = (compChoice - 1)%3;
    gameArray[row][col] = compXO;
    if(blockPlayer != 0)
    printf("\nThe computer blocked the players win on space: %d\n", compChoice);
    }
    //if the computer cannot win or block the player, it randomly chooses a spot
    while(compValid != 1)
    {
    compChoice = rand()%9+1;
    int row = (compChoice - 1)/3;
    int col = (compChoice - 1)%3;
    if(gameArray[row][col] != 'X' && gameArray[row][col] != 'O')
    {
     gameArray[row][col] = compXO;
     printf("\nThe computer picked space: %d\n", compChoice);
     compValid = 1;
    }//if


    }//while


    return ;
}
/*
* Function name: checkWin
*
* Parameters: character game array 3x3, character value representing any player (X or O)
*
* Return type: int value representing if the player won, (0 if loss 1 if won)
*
* Description: This function checks to see if the player won by searching each column, row, and diagnal cross for a three of a type,
* either X or O.
*
*/
int checkWin(char gameArray[3][3], char winXO)
{
    int winner = 0;

    //horizontal
    if((gameArray[0][0] == winXO) && (gameArray[0][1] == winXO) && (gameArray[0][2] == winXO))
        winner = 1;

    if((gameArray[1][0] == winXO) && (gameArray[1][1] == winXO) && (gameArray[1][2] == winXO))
        winner = 1;

    if((gameArray[2][0] == winXO) && (gameArray[2][1] == winXO) && (gameArray[2][2] == winXO))
        winner = 1;

    //vertical
    if((gameArray[0][0] == winXO) && (gameArray[1][0] == winXO) && (gameArray[2][0] == winXO))
        winner = 1;

    if((gameArray[0][1] == winXO) && (gameArray[1][1] == winXO) && (gameArray[2][1] == winXO))
    winner = 1;

    if((gameArray[0][2] == winXO) && (gameArray[1][2] == winXO) && (gameArray[2][2] == winXO))
        winner = 1;

    //diagnal
    if((gameArray[0][0] == winXO) && (gameArray[1][1] == winXO) && (gameArray[2][2] == winXO))
        winner = 1;

    if((gameArray[0][2] == winXO) && (gameArray[1][1] == winXO) && (gameArray[2][0] == winXO))
        winner = 1;


    return winner;
}

/*
* Function Name: computerBlock
*
* Parameters: character array 3x3, character value representing X or O
*
* Return type: int value representing which space the player can take if the
* the player is about to win.
*
* Description: In reality this is just a simple copy and paste of the
* computer brain that determines which space it can take to win. This function
* searches each space and searches for a win based on the character valued entered.
*/
int computerBlock(char gameArray[3][3], char compXO)
{
    int compValid = 0;
    int compChoice = 0;

    //check win space 1
    if(gameArray[0][0] == '1' && gameArray[0][1] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    if(gameArray[0][0] == '1' && gameArray[1][1] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    if(gameArray[0][0] == '1' && gameArray[1][0] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 1;
        compValid = 1;
    }
    //check win space 2
    if(gameArray[0][1] == '2' && gameArray[0][0] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 2;
        compValid = 1;
    }
    if(gameArray[0][1] == '2' && gameArray[1][1] == compXO && gameArray[2][1] == compXO)
    {
        compChoice = 2;
        compValid = 1;
    }
    //check win space 3
    if(gameArray[0][2] == '3' && gameArray[0][1] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    if(gameArray[0][2] == '3' && gameArray[1][2] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    if(gameArray[0][2] == '3' && gameArray[1][1] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 3;
        compValid = 1;
    }
    //check win space 4
    if(gameArray[1][0] == '4' && gameArray[1][1] == compXO && gameArray[1][2] == compXO)
    {
        compChoice = 4;
        compValid = 1;
    }
    if(gameArray[1][0] == '4' && gameArray[0][0] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 4;
        compValid = 1;
    }
    //check win space 5
    if(gameArray[1][1] == '5' && gameArray[1][0] == compXO && gameArray[1][2] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[0][1] == compXO && gameArray[2][1] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[0][0] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }
    if(gameArray[1][1] == '5' && gameArray[1][2] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 5;
        compValid = 1;
    }

    //check win space 6
    if(gameArray[1][2] == '6' && gameArray[1][1] == compXO && gameArray[1][0] == compXO)
    {
        compChoice = 6;
        compValid = 1;
    }
    if(gameArray[1][2] == '6' && gameArray[0][2] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 6;
        compValid = 1;
    }
    //check win space 7
    if(gameArray[2][0] == '7' && gameArray[2][1] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    if(gameArray[2][0] == '7' && gameArray[1][0] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    if(gameArray[2][0] == '7' && gameArray[1][1] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 7;
        compValid = 1;
    }
    //check win space 8
    if(gameArray[2][1] == '8' && gameArray[2][0] == compXO && gameArray[2][2] == compXO)
    {
        compChoice = 8;
        compValid = 1;
    }
    if(gameArray[2][1] == '8' && gameArray[1][1] == compXO && gameArray[0][1] == compXO)
    {
        compChoice = 8;
        compValid = 1;
    }
    //check win space 9
    if(gameArray[2][2] == '9' && gameArray[2][1] == compXO && gameArray[2][0] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }
    if(gameArray[2][2] == '9' && gameArray[1][2] == compXO && gameArray[0][2] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }
    if(gameArray[2][2] == '9' && gameArray[1][1] == compXO && gameArray[0][0] == compXO)
    {
        compChoice = 9;
        compValid = 1;
    }
    return compChoice;
}
