#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "MP-Functions.h"

// Initialize the 4x4 board with spaces
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Print the current state of the board
void printBoard(char board[SIZE][SIZE]) {
    printf("\n   1   2   3   4\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("   ---+---+---+---\n");
    }
    printf("\n");
}

// Attempt to place a mark ('U' or 'T') at board[row][col]
// Returns true if successful; false if the cell is already occupied
bool placeMark(char board[SIZE][SIZE], int row, int col, char mark) {
    if (board[row][col] != ' ')
        return false;
    board[row][col] = mark;
    return true;
}

// Randomly clear (set to ' ') one occupied tile on the board
// This function is called only after Uno's move.
void clearRandomOccupiedTile(char board[SIZE][SIZE]) {
    int occupiedCount = 0;
    int positions[SIZE * SIZE][2];  // to store (row, col) of occupied cells

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != ' ') {
                positions[occupiedCount][0] = i;
                positions[occupiedCount][1] = j;
                occupiedCount++;
            }
        }
    }

    // If there is at least one occupied tile, choose one at random to clear
    if (occupiedCount > 0) {
        int randomIndex = rand() % occupiedCount;
        int r = positions[randomIndex][0];
        int c = positions[randomIndex][1];
        board[r][c] = ' ';
        printf("[Random Clearing] Cleared tile at (%d, %d).\n", r + 1, c + 1);
    }
}

// Check for a winner or a tie.
// Winning conditions (W = C – T) are:
//   1) Top row: (1,1),(1,2),(1,3),(1,4)
//   2) Anti-diagonal: (1,4),(2,3),(3,2),(4,1)
//   3) Bottom row: (4,1),(4,2),(4,3),(4,4)
// Additionally, if no free cell remains (F = ∅), return 'D' (Dos wins tie).
char checkWinner(char board[SIZE][SIZE]) {
    // Check top row
    if (board[0][0] != ' ' &&
        board[0][0] == board[0][1] &&
        board[0][1] == board[0][2] &&
        board[0][2] == board[0][3]) {
        return board[0][0];
    }
    
    // Check anti-diagonal (from top-right to bottom-left)
    if (board[0][3] != ' ' &&
        board[0][3] == board[1][2] &&
        board[1][2] == board[2][1] &&
        board[2][1] == board[3][0]) {
        return board[0][3];
    }
    
    // Check bottom row
    if (board[3][0] != ' ' &&
        board[3][0] == board[3][1] &&
        board[3][1] == board[3][2] &&
        board[3][2] == board[3][3]) {
        return board[3][0];
    }
    
    // Check for tie: if no free cell exists, then F is empty.
    bool tie = true;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                tie = false;
                break;
            }
        }
        if (!tie)
            break;
    }
    if (tie)
        return 'D';  // 'D' represents Dos wins (tie)

    return ' ';  // No winner or tie yet.
}
