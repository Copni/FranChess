//
// Created by IamaU on 20/08/2025.
//
#include "displacement.h"

void swapPiece(PIECE ***board, PIECE *p, PIECE *q) {
    int tmpX = p->x;
    int tmpY = p->y;

    board[p->y][p->x] = q;
    p->x = q->x;
    p->y = q->y;

    board[q->y][q->x] = p;
    q->x = tmpX;
    q->y = tmpY;
}

int movePiece(PIECE ***board, PIECE *p, PIECE *q) {
    if (board != NULL && p != NULL && q != NULL) {
        if (q->color == p->color) {
            printf("Error: Cannot move to a square occupied by a piece of the same color.\n");
            return -1;
        }
        PIECE_TYPE type = p->type;
        if (type) {
            q->color = grey;
            q->type = empty;
            q->symbole = '*';
        }
        swapPiece(board, q, p);
        return fetchScore(type);
    }
    return -1;
}

int fetchScore(PIECE_TYPE type) {
    switch (type) {
        case empty:
            return 0;
        case pawn:
            return 1;
        case knight:
            return 3;
        case bishop:
            return 3;
        case rook:
            return 5;
        case queen:
            return 9;
        case king:
            return 1000;
        default:
            return 0;
    }
}

// Penser à faire un switch en fonction du type de coup (rock, classique, etc.)
// Un coup est légal si :
// - La pièce n'est pas clouée
// - Le roi n'est pas en échec après le coup
// - Le déplacement est conforme aux règles de la pièce

// Idée : on exécute le coup sur un plateau temporaire et si les conditions sont remplies, le coup est légal
int executeMove(GAMESTATE *g, MOVE *move, COLOR color) {
    switch (move->type) {
        case classic:
            // Retrieve the piece to move and the target square
            char * m = move->move;
            PIECE * p = findPiece(m, g->board, color);
            if (p == NULL) {
                printf("Piece not found.\n");
                return 0;
            }
            PIECE * q = g->board[m[4] - '1'][m[3] - 'a'];

            // Verification logic
            if (isPinned(p, g) != NULL) {
                printf("This piece is pinned and cannot move: ");
                printPiece(p);
                return 0; // Piece is pinned
            }

            // Execute the move temporarily, then check is everything's fine
            GAMESTATE * h = copy_game_state(g);
            movePiece(h->board, p, q);
            int ischecked = color == white ? h->is_w_king_in_check : h->is_b_king_in_check;
            // mettre à jour les positions, pensez à faire ça pour le roi aussi
            if (ischecked) {
                printf("Move would leave king in check. Illegal move.\n");
                // Clean up
                deleteBoard(h->board);
                free(h);
                h = NULL;
                return 0;
            }





            break;
        case castle:
            switch (color) {
                case white:
                    if (g->has_w_king_moved == 0 && g->has_hw_rook_moved == 0 && g->board[0][5]->type == empty &&
                        g->board[0][6]->type == empty && isThreatened(g->board[0][4], g->board, white) == 0 &&
                        isThreatened(g->board[0][5], g->board, white) == 0 && isThreatened(
                            g->board[0][5], g->board, white) == 0) {
                        // Temporary castle
                        swapPiece(g->board, g->board[0][4], g->board[0][6]);
                        swapPiece(g->board, g->board[0][7], g->board[0][5]);
                        g->has_w_king_moved = 1;
                        g->has_hw_rook_moved = 1;
                        return 1;
                    }
                    break;
                case black:
                    if (g->has_b_king_moved == 0 && g->has_hb_rook_moved == 0 && g->board[7][5]->type == empty &&
                        g->board[7][6]->type == empty && isThreatened(g->board[7][4], g->board, black) == 0 &&
                        isThreatened(g->board[7][5], g->board, black) == 0 && isThreatened(
                            g->board[7][6], g->board, black) == 0) {
                        // Temporary castle
                        swapPiece(g->board, g->board[7][4], g->board[7][6]);
                        swapPiece(g->board, g->board[7][7], g->board[7][5]);
                        g->has_b_king_moved = 1;
                        g->has_hb_rook_moved = 1;
                        return 1;
                    }
                    break;
                default:
                    return 0;// Temporary castle
            }
            break;
        case long_castle:
            switch (color) {
                case white:
                    if (g->has_w_king_moved == 0 && g->has_aw_rook_moved == 0 && g->board[0][1]->type == empty &&
                    g->board[0][2]->type == empty &&
                    g->board[0][3]->type == empty && isThreatened(g->board[0][4], g->board, white) == 0 &&
                        isThreatened(g->board[0][3], g->board, white) == 0 && isThreatened(
                            g->board[0][2], g->board, white) == 0) {
                        // Temporary castle
                        swapPiece(g->board, g->board[0][4], g->board[0][2]);
                        swapPiece(g->board, g->board[0][0], g->board[0][3]);
                        g->has_w_king_moved = 1;
                        g->has_aw_rook_moved = 1;
                        return 1;
                            }
                    break;
            case black:
                    if (g->has_b_king_moved == 0 && g->has_ab_rook_moved == 0 && g->board[7][1]->type == empty &&
                    g->board[7][2]->type == empty &&
                    g->board[7][3]->type == empty && isThreatened(g->board[7][4], g->board, black) == 0 &&
                        isThreatened(g->board[7][3], g->board, black) == 0 && isThreatened(
                            g->board[7][2], g->board, black) == 0) {
                        // Temporary castle
                        swapPiece(g->board, g->board[7][4], g->board[7][2]);
                        swapPiece(g->board, g->board[7][0], g->board[7][3]);
                        g->has_b_king_moved = 1;
                        g->has_ab_rook_moved = 1;
                        return 1;
                            }
                    break;
            default:
                    return 0;
            }
        default:
            return 0;
    }
}

    /*
    PIECE * p = findPiece(m, g->board, color);
    if (p == NULL) {
        printf("No piece found for the move: %s\n", m);
        return 0; // No piece found
    }
    PIECE * q = g->board[m[4] - '1'][m[3] - 'a'];

    GAMESTATE * h = copy_game_state(g);
    int target = isThreatened(q, g->board, color * -1);
    int ischecked = color == white ? g->is_w_king_in_check : g->is_b_king_in_check;



    if (isPinned(p, g) != NULL) {
        printf("This piece is pinned and cannot move: ");
        printPiece(p);
        return 0; // Piece is pinned
    }
    */

