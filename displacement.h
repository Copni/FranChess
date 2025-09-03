//
// Created by IamaU on 20/08/2025.
//

#ifndef ALGECHESS_DISPLACEMENT_H
#define ALGECHESS_DISPLACEMENT_H
#include "threat.h"

void swapPiece (PIECE *** board, PIECE * p1, PIECE * q);
int movePiece (PIECE *** board, PIECE * p, PIECE * q);
int fetchScore(PIECE_TYPE type);
int executeMove (GAMESTATE * g, MOVE * move, COLOR color);
void addScore (GAMESTATE * g, PIECE * p);

#endif //ALGECHESS_DISPLACEMENT_H