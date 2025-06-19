//
// Created by IamaU on 14/04/2025.
//

#ifndef THREAT_H
#define THREAT_H
#include "findPiece.h"

int isThreatened(int x, int y, PIECE * * * board, COLOR color);
PIECE * * isPinned(PIECE ** piece, PIECE * * * board, COLOR color);
// Return an array of 2 PIECE *
// Index 0 = attacking piece
// Index 1 = defended piece


int * *  getAttackedSquares(PIECE * * * board, COLOR color);
int * isMovePossible (char * move, PIECE * * * board, COLOR color);

#endif //THREAT_H
