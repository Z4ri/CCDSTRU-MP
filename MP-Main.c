#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "MP-Functions.h"

void displayMenu() {
    printf("=====================================\n");
    printf("         Welcome to Tres & Uno       \n");
    printf("=====================================\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
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
		} else {
			// Switch player for next turn
			currentPlayer = (currentPlayer == 'U') ? 'T' : 'U';
		}
	}
	// After the game ends, automatically return to the main menu
	printf("\nReturning to the main menu...\n\n");
}

int main(void) {
	int choice;

	while (true) {
		// Main menu loop
		displayMenu();
		if (scanf("%d", &choice) != 1) {
			printf("Invalid input. Exiting...\n");
			return 1;
		}
		if (choice == 1) {
			mainGame();
		} else if (choice == 2) {
			printf("Exiting the game. Goodbye!\n");
			return 0; // Exit the program
		} else {
			printf("Invalid choice. Please try again.\n");
		}
	}
}
