#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "MP-Functions.c"
#include "MP-Functions.h"

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
            displayInstructions();
            printf("Press ENTER to return to the main menu...");
            while(getchar() != '\n'); // Clear input buffer
            getchar(); // Wait for the user to press ENTER
        } else if (choice == 3) {
            printf("Thank you for playing!\n");
            return 0; // Exit the program
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
