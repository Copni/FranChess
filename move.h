//
// Created by IamaU on 24/12/2023.
//

#ifndef CHESSNOTATIONTRAINING_MOVE_H
#define CHESSNOTATIONTRAINING_MOVE_H
#include "board.h"

typedef enum{
    castle = 2, long_castle = 3, classic = 1
}MOVE_TYPE;

typedef struct {
    char * move;
    MOVE_TYPE type;
} MOVE;

// Créer une fonction qui découpe la chaîne de caractère en une liste de paramètre

int length(char * str);
int same_string(char * str1, char * str2);
int isPiece(char c);
MOVE * getMove();



#endif //CHESSNOTATIONTRAINING_MOVE_H
