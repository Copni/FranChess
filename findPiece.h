//
// Created by IamaU on 07/11/2024.
//

#ifndef LEGAL_H
#define LEGAL_H
#include "move.h"

void addElement(int ***foundPiece, int *pieceCount, int x, int y);
void removeElement(int ***array, int *size, int index);
int * * findPawn (char * move, PIECE * * * board, COLOR color);
int * * findKnight(char *move, PIECE ***board, COLOR color);
int * * findBishop(char * move, PIECE * * * board, COLOR color);
int * * findRook (char * move, PIECE * * * board, COLOR color);
int * * findQueen(char *move, PIECE ***board, COLOR color);
int * * findKing(char *move, PIECE ***board, COLOR color);



*/
#endif //LEGAL_H
