//
// Created by IamaU on 16/06/2025.
//
#include "gamestate.h"

GAMESTATE * init_board_data() {
    GAMESTATE * g = (GAMESTATE *) malloc(sizeof(GAMESTATE));
    g->board = createBoard();
    setBoard(g->board);
    g->black_score = 0;
    g->white_score = 0;
    g->has_ab_rook_moved = 0;
    g->has_hb_rook_moved = 0;
    g->has_aw_rook_moved = 0;
    g->has_hw_rook_moved = 0;
    g->has_w_king_moved = 0;
    g->has_b_king_moved = 0;
    g->is_w_king_in_check = 0;
    g->is_b_king_in_check = 0;
    g->w_king = g->board[0][4];
    g->b_king = g->board[7][4];
    return g;
}

GAMESTATE * gen_board_data(PIECE * * * board) {
    GAMESTATE * g = (GAMESTATE *) malloc(sizeof(GAMESTATE));
    g->board = board;
    g->black_score = 0;
    g->white_score = 0;
    g->has_ab_rook_moved = 0;
    g->has_hb_rook_moved = 0;
    g->has_aw_rook_moved = 0;
    g->has_hw_rook_moved = 0;
    g->has_w_king_moved = 0;
    g->has_b_king_moved = 0;
    g->is_w_king_in_check = 0;
    g->is_b_king_in_check = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->type == king && board[i][j]->color == white) {
                g->w_king = board[i][j];
            } else if (board[i][j]->type == king && board[i][j]->color == black) {
                g->b_king = board[i][j];
            }
        }
    }
    return g;
}

void display_board(GAMESTATE * g) {
    printf("Black score: %d\n", g->black_score);
    printf("White score: %d\n", g->white_score);
    printf("Black rook on column a moved: %s\n", g->has_ab_rook_moved ? "True" : "False");
    printf("Black rook on column h moved: %s\n", g->has_hb_rook_moved ? "True" : "False");
    printf("White rook on column a moved: %s\n", g->has_aw_rook_moved ? "True" : "False");
    printf("White rook on column h moved: %s\n", g->has_hw_rook_moved ? "True" : "False");
    printf("White king has moved: %s\n", g->has_w_king_moved ? "True" : "False");
    printf("Black king has moved: %s\n", g->has_b_king_moved ? "True" : "False");
}