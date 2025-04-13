//
// Created by IamaU on 20/02/2024.
//
#include "move.h"

int length(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int same_string(char *str1, char *str2) {
    if (length(str1) == length(str2)) {
        int i = 0;
        while ((str1[i] == str2[i]) && str1[i] != '\n') {
            i++;
        }
        if (i == length(str1)) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int isPiece(char c) {
    PIECE_TYPE const piece_list[] = {pawn, rook, knight, bishop, king, queen};
    for (int i = 0; i < 6; i++) {
        if (c == piece_list[i]) {
            return 1;
        }
    }
    return 0;
}

char *getMove() {
    //get the move
    char inputMove[6];
    char *outputMove = malloc(7 * sizeof(char));
    for (int i = 0; i < 7; i++) {
        outputMove[i] = '0';
    }
    outputMove[7] = '\0';
    /* the input move is converted in a fixed string:
    Index 0: piece type
    Index 1: complementary line or row index
    Index 2: 'x' if a piece is eaten
    Index 3: row index
    Index 4: line index
    Index 5: promoted piece type
    Index 6: '+' or '#' if check or mat
    Everything is '0' by default
    */


    fgets(inputMove, 7, stdin);
    int moveLength = length(inputMove);

    for (int i = 0; i < moveLength; i++) {
        if (inputMove[i] == '\n') {
            inputMove[i] = '\0';
            moveLength--;
        }
    }
    if (moveLength < 2 || moveLength > 6) {
        return NULL;
    }
    if (same_string(inputMove, "O-O-O") || same_string(inputMove, "O-O")) {
        return outputMove;
    }
    // Find row index to use it as a reference index next
    int line = 0;
    for (int i = moveLength - 1; i >= 0; i--) {
        if (inputMove[i] > '0' && inputMove[i] < '9') {
            if (i == 0) {
                return NULL;
            }
            line = i;
            outputMove[4] = inputMove[line];
            break;
        }
    }

    // Reformate the input move in a output move according the next

    PIECE_TYPE piece_list[] = {pawn, rook, knight, bishop, king, queen};

    if (inputMove[line - 1] > 'a' && inputMove[line - 1] <= 'h') {
        outputMove[3] = inputMove[line - 1];
    } else {
        return NULL;
    }

    if (moveLength == 2) {
        return outputMove;
    }

    if (inputMove[line + 1] != '\0') {
        if (inputMove[line + 2] != '\0') {
            if (inputMove[line + 2] == '+' || inputMove[line + 2] == '#') {
                outputMove[6] = inputMove[line + 2];
            } else {
                return NULL;
            }
            if (isPiece(inputMove[line + 1])) {
                outputMove[5] = inputMove[line + 1];
            } else {
                return NULL;
            }
        }
        if (inputMove[line + 1] == '+' || inputMove[
                line + 1] == '#') {
            outputMove[5] = inputMove[line + 1];
        } else {
            if (isPiece(inputMove[line + 1])) {
                outputMove[5] = inputMove[line + 1];
            } else {
                return NULL;
            }
        }
    }
    if (line == 1) {
        return outputMove;
    }

    if (line == 2) {
        if (isPiece(inputMove[0])) {
            outputMove[0] = inputMove[0];
            return outputMove;
        }
        if (inputMove[0] == 'x') {
            outputMove[2] = 'x';
            return outputMove;
        }
        return NULL;
    }
    if (line == 3) {
        if (inputMove[1] == 'x') {
            if ((inputMove[0] >= 'a' && inputMove[0] <= 'h') || (inputMove[0] >= '1' && inputMove[0] <= '8')){
                outputMove[2] = 'x';
                outputMove[1] = inputMove[0];
                return outputMove;
            }
            if (isPiece(inputMove[0])) {
                outputMove[2] = 'x';
                outputMove[0] = inputMove[0];
                return outputMove;
            }
            return NULL;
        }
        if (((inputMove[1] >= 'a' && inputMove[1] <= 'h') || (inputMove[1] >= '1' && inputMove[1] <= '8')) && (
                isPiece(inputMove[0]))) {
            outputMove[0] = inputMove[0];
            outputMove[1] = inputMove[1];
            return outputMove;
        }
        return NULL;
    }
    if (line == 4) {
        if (((inputMove[1] >= 'a' && inputMove[1] <= 'h') || (inputMove[1] >= '1' && inputMove[1] <= '8')) && (
                isPiece(inputMove[0])) && (inputMove[2] == 'x')) {
            outputMove[0] = inputMove[0];
            outputMove[1] = inputMove[1];
            outputMove[2] = inputMove[2];

            // In this condition is respected then inputMove is finished by "\0\0" and mess up the previous code
            outputMove[6] = '0';
            outputMove[7] = '\0';
            return outputMove;
        }
    }
    return NULL;
}

