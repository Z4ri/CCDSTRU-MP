#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "MP-Functions.h"

int main(void) {
    char board[SIZE][SIZE];
    int row, col;
    bool gameOver = false;
    char winner = ' ';
    
    // Uno is represented by 'U' and Tres by 'T'
    // Dos is used only for tie, represented by 'D' when the board is full.
    char currentPlayer = 'U';
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    // Initialize the board
    initializeBoard(board);
    
    // Main game loop
    while (!gameOver) {
        printBoard(board);
        printf("Current Player: %s\n", (currentPlayer == 'U') ? "Uno (U)" : "Tres (T)");
        printf("Enter row [1-4] and column [1-4] separated by a space: ");
        
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        
        // Validate input range
        if (row < 1 || row > 4 || col < 1 || col > 4) {
            printf("Coordinates out of range. Try again.\n");
            continue;
        }
        
        // Attempt to place the mark
        if (!placeMark(board, row - 1, col - 1, currentPlayer)) {
            printf("That cell is already occupied. Try again.\n");
            continue;
        }
        
        // Only clear a random tile after Uno's turn
        if (currentPlayer == 'U') {
            clearRandomOccupiedTile(board);
        }
        
        // Check for winner or tie
        winner = checkWinner(board);
        if (winner != ' ') {
            printBoard(board);
            if (winner == 'U')
                printf("Player Uno (U) wins!\n");
            else if (winner == 'T')
                printf("Player Tres (T) wins!\n");
            else if (winner == 'D')
                printf("Game over: Dos wins (tie)!\n");
            gameOver = true;
            break;
        }
        
        // Switch player for next turn
        currentPlayer = (currentPlayer == 'U') ? 'T' : 'U';
    }
    
    printf("Game over.\n");
    return 0;
}
