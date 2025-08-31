//
// Created by IamaU on 20/08/2025.
//

#ifndef ALGECHESS_DISPLACEMENT_H
#define ALGECHESS_DISPLACEMENT_H
#include "threat.h"

void swapPiece (PIECE *** board, PIECE * p, PIECE * q);
void movePiece (PIECE *** board, PIECE * p, PIECE * q);
int isLegalMove (GAMESTATE * g, char * move, COLOR color);

#endif //ALGECHESS_DISPLACEMENT_H