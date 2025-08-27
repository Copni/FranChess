//
// Created by IamaU on 20/08/2025.
//

#ifndef ALGECHESS_DISPLACEMENT_H
#define ALGECHESS_DISPLACEMENT_H
#include "threat.h"

void displacePiece (PIECE *** board, PIECE * p1, PIECE * p2);
int isLegalMove (GAMESTATE * g, char * move, COLOR color);

#endif //ALGECHESS_DISPLACEMENT_H