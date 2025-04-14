//
// Created by IamaU on 14/04/2025.
//

#ifndef THREAT_H
#define THREAT_H
#include "findPiece.h"

int isThreatened(int x, int y, PIECE * * * board, COLOR color);
int isPinned(PIECE ** piece, PIECE * * * board, COLOR color);
int * *  getAttackedSquares(PIECE * * * board, COLOR color);
int * isMovePossible (char * move, PIECE * * * board, COLOR color);

#endif //THREAT_H
