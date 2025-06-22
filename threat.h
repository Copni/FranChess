//
// Created by IamaU on 14/04/2025.
//

#ifndef THREAT_H
#define THREAT_H
#include "findPiece.h"
#include "gamestate.h"

int isThreatened(const PIECE * p, PIECE * * * board, COLOR color);
PIECE * isPinned(PIECE * piece, GAMESTATE * g);
int * * getAttackedSquares(PIECE * * * board, COLOR color);
int isLegal (const char * move, GAMESTATE * g, COLOR color);

#endif //THREAT_H
