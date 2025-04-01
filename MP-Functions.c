#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "MP-Functions.h"


void displayMenu() {
    printf("=====================================\n");
    printf("            Welcome to Zed           \n");
    printf("=====================================\n");
    printf("1. Start Game\n");
    printf("2. How to play?\n");
    printf("3. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

void displayInstructions() {
    printf("Instructions:\n");
    printf("1. Players take turns placing their marks on the board.\n");
    printf("2. Tres is represented by 'T' and Uno by 'U'.\n");
    printf("3. After Uno's turn, a random occupied tile will be cleared.\n");
    printf("4. The game ends when one player wins or if there is a tie.\n");
    printf("5. Enjoy the game!\n\n");

    // Top Row win scenario
    printf("Winning Pattern a) Top Row win:\n");
    printf("     1   2   3   4\n");
    printf(" 1   X | X | X | X\n");
    printf("    ---+---+---+---\n");
    printf(" 2     |   |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 3     |   |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 4     |   |   |  \n\n");

    // Anti-Diagonal win scenario
    printf("Winning Pattern b) Anti-Diagonal win:\n");
    printf("     1   2   3   4\n");
    printf(" 1     |   |   | X\n");
    printf("    ---+---+---+---\n");
    printf(" 2     |   | X |  \n");
    printf("    ---+---+---+---\n");
    printf(" 3     | X |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 4   X |   |   |  \n\n");

    // Bottom Row win scenario
    printf("Winning Pattern c) Bottom Row win:\n");
    printf("     1   2   3   4\n");
    printf(" 1     |   |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 2     |   |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 3     |   |   |  \n");
    printf("    ---+---+---+---\n");
    printf(" 4   X | X | X | X\n\n");
}

void mainGame() {

    char board[SIZE][SIZE];
    int row, col;
    bool gameOver;
    char winner;
    // Tres is represented by 'T' and Uno by 'U'
    // Dos is used only for tie, represented by 'D' when the board is full.
    char currentPlayer = 'T'; // Start with Tres

    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    // Initialize the board
    initializeBoard(board);
    gameOver = false;
    winner = ' ';

    // Main game loop
    while (!gameOver) {
        printBoard(board);
        printf("Current Player: %s\n", (currentPlayer == 'U') ? "Uno (U)" : "Tres (T)");
        printf("Enter row [1-4] and column [1-4] separated by a space: ");

        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Exiting...\n");
            return;
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

        // Check for a win immediately after the move
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

        // Only clear a random tile after Uno's move if no win yet
        if (currentPlayer == 'U') {
            clearRandomOccupiedTile(board);
            // Check for win after clearing
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
        }

        // Switch player for next turn
        currentPlayer = (currentPlayer == 'U') ? 'T' : 'U';
    }
    
    // After the game ends, automatically return to the main menu
    printf("\nReturning to the main menu...\n\n");
}

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
