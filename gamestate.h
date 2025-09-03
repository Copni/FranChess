//
// Created by IamaU on 16/06/2025.
//

#ifndef BOARD_DATA_H
#define BOARD_DATA_H
#include "board.h"

typedef struct {
    PIECE *** board;
    int black_score;
    int white_score;
    int has_ab_rook_moved;
    int has_hb_rook_moved;
    int has_aw_rook_moved;
    int has_hw_rook_moved;
    int has_w_king_moved;
    int has_b_king_moved;
    int is_w_king_in_check;
    int is_b_king_in_check;
    PIECE * w_king;
    PIECE * b_king;
}GAMESTATE;

GAMESTATE * init_board_data();
GAMESTATE * gen_board_data(PIECE * * * board);
GAMESTATE * copy_game_state(GAMESTATE * g);
void display_board(GAMESTATE * g);
#endif //BOARD_DATA_H
