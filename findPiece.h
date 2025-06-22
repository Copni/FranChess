//
// Created by IamaU on 07/11/2024.
//

#ifndef LEGAL_H
#define LEGAL_H
#include "move.h"

void addElement(int ***foundPiece, int *pieceCount, int x, int y);
void removeElement(int ***array, int *size, int index);
int * * findPawn (const char * move, PIECE * * * board, COLOR color);
int * * findKnight(const char *move, PIECE ***board, COLOR color);
int * * findBishop(const char * move, PIECE * * * board, COLOR color);
int * * findRook (const char * move, PIECE * * * board, COLOR color);
int * * findQueen(const char *move, PIECE ***board, COLOR color);
int * * findKing(const char *move, PIECE ***board, COLOR color);
int * * findPiece(char * move, PIECE * * * board, COLOR color);

#endif //LEGAL_H
