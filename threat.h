//
// Created by IamaU on 14/04/2025.
//

#ifndef THREAT_H
#define THREAT_H
#include "findPiece.h"
#include "gamestate.h"

int isThreatened(int x, int y, PIECE * * * board, COLOR color);
PIECE * isPinned(PIECE * piece, GAMESTATE * g);



int * *  getAttackedSquares(PIECE * * * board, COLOR color);
int * isMovePossible (char * move, PIECE * * * board, COLOR color);

#endif //THREAT_H
