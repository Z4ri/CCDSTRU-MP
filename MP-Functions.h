#ifndef MP_FUNCTIONS_H
#define MP_FUNCTIONS_H

#include <stdbool.h>

#define SIZE 4

void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
bool placeMark(char board[SIZE][SIZE], int row, int col, char mark);
void clearRandomOccupiedTile(char board[SIZE][SIZE]);
char checkWinner(char board[SIZE][SIZE]);

#endif // MP_FUNCTIONS_H