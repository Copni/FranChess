//
// Created by IamaU on 07/11/2024.
//

#ifndef LEGAL_H
#define LEGAL_H
#include "move.h"


/* Previous version returning an array of array with the coordinates of the found pieces
   Need to filter the array afterward to find the right piece

void addElement(int ***foundPiece, int *pieceCount, int x, int y);
void removeElement(int ***array, int *size, int index);
int * * findPawn (const char * move, PIECE * * * board, COLOR color);
int * * findKnight(const char *move, PIECE ***board, COLOR color);
int * * findBishop(const char * move, PIECE * * * board, COLOR color);
int * * findRook (const char * move, PIECE * * * board, COLOR color);
int * * findQueen(const char *move, PIECE ***board, COLOR color);
int * * findKing(const char *move, PIECE ***board, COLOR color);
int * * findPiece(char * move, PIECE * * * board, COLOR color);
*/


// New version returning a pointer to the found piece

void addElement(PIECE ***foundPieces, int *count, PIECE *piece);
PIECE * findPawn (const char * move, PIECE * * * board, COLOR color);
PIECE * findKnight(const char *move, PIECE ***board, COLOR color);
PIECE * findBishop(const char * move, PIECE * * * board, COLOR color);
PIECE * findRook (const char * move, PIECE * * * board, COLOR color);
PIECE * findQueen(const char *move, PIECE ***board, COLOR color);
PIECE * findKing(const char *move, PIECE ***board, COLOR color);
PIECE * findPiece(char * move, PIECE * * * board, COLOR color);

#endif //LEGAL_H
