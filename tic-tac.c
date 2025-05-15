#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

char board[SIZE][SIZE];
char currentPlayer;

void initializeBoard();
void printBoard();
int makeMove(int row, int col);
int checkWinner();
int isDraw();
void switchPlayer();
void playGame();
void welcomeMessage();
void clearInputBuffer();

// Main Function

int main() 
{
    welcomeMessage();
    playGame();
    return 0;
}

// Welcome screen

void welcomeMessage() 
{
    
    printf("=====================================\n");
    printf("         TIC-TAC-TOE IN C            \n");
    printf("=====================================\n");
    printf("Player 1: X\n");
    printf("Player 2: O\n\n");

}

// Initialize the board

void initializeBoard() 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            board[i][j] = ' ';
        }
    }
}

// Display the board

void printBoard() 
{
    printf("\n");
    for (int i = 0; i < SIZE; i++) 
    {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != SIZE - 1) 
        {
            printf("\n---|---|---\n");
        }
    }
    printf("\n\n");
}

// Make a move

int makeMove(int row, int col) 
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) 
    
    {
        printf("Invalid move. Position out of range.\n");
        return 0;
    }

    if (board[row][col] != ' ') 
    {
        printf("Invalid move. Cell already taken.\n");
        return 0;
    }

    board[row][col] = currentPlayer;
    return 1;
}

// Check for winner

int checkWinner() 
{
    for (int i = 0; i < SIZE; i++) 
    {
        // Check rows
        
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer) 
        
        {
            return 1;
        }
        
        // Check columns
        
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer) 
        
        {
            return 1;
        }
    }

    // Check diagonals
    
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer) 
    
    {
        return 1;
    }

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer) 
    
    {
        return 1;
    }

    return 0;
}

// Check for draw

int isDraw() 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (board[i][j] == ' ') 
            {
                return 0;
            }
        }
    }
    return 1;
}

// Switch players

void switchPlayer() 
{
    if (currentPlayer == 'X') 
    
    {
        currentPlayer = 'O';
    } 
    
    else 
    
    {
        currentPlayer = 'X';
    }
}

// Main game loop

void playGame() 
{
    int row, col;
    int validMove;

    initializeBoard();
    currentPlayer = 'X';

    while (1) 
    {
        printBoard();
        printf("Player %c, enter your move (row[1-3] col[1-3]): ", currentPlayer);
        validMove = scanf("%d %d", &row, &col);
        if (validMove != 2) 
        {
            
            printf("Invalid input. Please enter two numbers.\n");
            clearInputBuffer();
            continue;
        }

        row--;
        col--;

        if (!makeMove(row, col)) 
        {
            continue;
        }

        if (checkWinner()) 
        {
            
            printBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (isDraw()) 
        {
            
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        switchPlayer();
    }
}

// Clear input buffer to handle invalid entries

void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
