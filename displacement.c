//
// Created by IamaU on 20/08/2025.
//
#include "displacement.h"

void swapPiece (PIECE *** board, PIECE * p, PIECE * q) {
    if ( board != NULL && p != NULL && q != NULL) {
        PIECE * tmp = q;
        deletePiece(q);
        printPiece(tmp);

    } else {
        printf("Pointer error: board, p1, or p2 is NULL.\n");
    }
}

void movePiece (PIECE *** board, PIECE * p, PIECE * q) {
    if (board != NULL && p != NULL && q != NULL) {
        if (q->type != empty) {
            board[q->y][q->x] = createPiece(empty, grey);
            deletePiece(q);
        }
        swapPiece(board, p, q);
    }
    else {
        printf("Pointer error: board, p1, or p2 is NULL.\n");
    }
}

// Penser à faire un switch en fonction du type de coup (rock, classique, etc.)
// Un coup est légal si :
// - La pièce n'est pas clouée
// - Le roi n'est pas en échec après le coup
// - Le déplacement est conforme aux règles de la pièce

// Idée : on exécute le coup sur un plateau temporaire et si les conditions sont remplies, le coup est légal
int isLegalMove (GAMESTATE * g, char * move, COLOR color) {
    PIECE * p = findPiece(move, g->board, color);
    PIECE * q = g->board[move[4] - '1'][move[3] - 'a'];

    int target = isThreatened(q, g->board, color * -1);

    int ischecked = color == white ? g->is_w_king_in_check : g->is_b_king_in_check;

    if (p == NULL) {
        printf("No piece found for the move: %s\n", move);
        return 0; // No piece found
    }

    if (isPinned(p, g) != NULL) {
        printf("This piece is pinned and cannot move: ");
        printPiece(p);
        return 0; // Piece is pinned
    }

}