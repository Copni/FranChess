//
// Created by IamaU on 23/12/2023.
//

#ifndef CHESSNOTATIONTRAINING_BOARD_H
#define CHESSNOTATIONTRAINING_BOARD_H
#include <stdio.h>
#include "piece.h"
#include <windows.h>

#define white_king   0x2654 // ♔
#define white_queen  0x2655 // ♕
#define white_rook   0x2656 // ♖
#define white_bishop 0x2657 // ♗
#define white_knight 0x2658 // ♘
#define white_pawn   0x2659 // ♙
#define black_king   0x265A // ♚
#define black_queen  0x265B // ♛
#define black_rook   0x265C // ♜
#define black_bishop 0x265D // ♝
#define black_knight 0x265E // ♞
#define black_pawn   0x265F // ♟

PIECE * * * createBoard();
void setBoard(PIECE * * *);
void setEmpty(PIECE * * *board);
void displayBoard(PIECE * * *, COLOR);
void displayBoardv2(PIECE * * *, COLOR);
void saveBoard(PIECE * * *, char * fileName);
PIECE * * * loadBoard(char * fileName);
void deleteBoard(PIECE * * *);

#endif //CHESSNOTATIONTRAINING_BOARD_H
