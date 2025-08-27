//
// Created by IamaU on 20/08/2025.
//
#include "displacement.h"

void displacePiece (PIECE *** board, PIECE * p1, PIECE * p2) {
    if ( board != NULL && p1 != NULL && p2 != NULL) {
        board[p1->y][p1->x] = p2;
        board[p2->y][p2->x] = p1;
        const int tempX = p1->x;
        const int tempY = p1->y;
        p1->x = p2->x;
        p1->y = p2->y;
        p2->x = tempX;
        p2->y = tempY;
    } else {
        printf("Pointer error: board, p1, or p2 is NULL.\n");
    }
}

// Penser à faire un switch en fonction du type de coup (rock, classique, etc.)
int isLegalMove (GAMESTATE * g, char * move, COLOR color) {
    PIECE * p = findPiece(move, g->board, color);
    PIECE * q = g->board[move[4] - '1'][move[3] - 'a'];
    int ischecked = color == white ? g->is_w_king_in_check : g->is_b_king_in_check;

    if (p == NULL) {
        printf("No piece found for the move: %s\n", move);
        return 0; // No piece found
    }

    if () {

    }

}