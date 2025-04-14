//
// Created by IamaU on 22/12/2023.
//

#ifndef CHESSNOTATIONTRAINING_PIECE_H
#define CHESSNOTATIONTRAINING_PIECE_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef enum
{
    pawn = 'P', knight = 'N', bishop = 'B', rook = 'R', queen = 'Q', king= 'K', empty = '*'
} PIECE_TYPE;

typedef enum
{
    black = -1, white = 1, grey = 0
} COLOR;

typedef enum
{
    a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7
} ROW;

typedef struct {
    PIECE_TYPE type;
    COLOR color;
    char symbole;
}PIECE;

PIECE * createPiece(PIECE_TYPE type, COLOR color);
void printPiece(PIECE * piece);
void deletePiece(PIECE *);

#endif //CHESSNOTATIONTRAINING_PIECE_H