//
// Created by IamaU on 23/12/2023.
//
#include "board.h"
#include <locale.h>

PIECE * * *createBoard() {
    PIECE * * *board = (PIECE * * *) malloc(8 * sizeof(PIECE * *));
    for (int i = 0; i < 8; i++) {
        board[i] = (PIECE * *) malloc(8 * sizeof(PIECE *));
        for (int j = 0; j < 8; j++) {
            board[i][j] = NULL;
        }
    }
    return board;
}

void setBoard(PIECE * * *board) {
    if (board == NULL) {
        printf("Failed to set up board\n");
        return;
    }
    for (int i = 0; i < 8; i++) {
        board[1][i] = createPiece(pawn, white, i, 1);
    }
    board[0][0] = createPiece(rook, white, 0, 0);
    board[0][7] = createPiece(rook, white, 0, 7);
    board[0][1] = createPiece(knight, white, 0, 1);
    board[0][6] = createPiece(knight, white, 0, 6);
    board[0][2] = createPiece(bishop, white, 0, 2);
    board[0][5] = createPiece(bishop, white, 0, 5);
    board[0][4] = createPiece(king, white, 0, 4);
    board[0][3] = createPiece(queen, white, 0, 3);
    for (int i = 0; i < 8; i++) {
        board[6][i] = createPiece(pawn, black, 6, i);
    }
    board[7][0] = createPiece(rook, black, 7, 0);
    board[7][7] = createPiece(rook, black, 7, 7);
    board[7][1] = createPiece(knight, black, 7, 1);
    board[7][6] = createPiece(knight, black, 7, 6);
    board[7][2] = createPiece(bishop, black, 7, 2);
    board[7][5] = createPiece(bishop, black, 7, 5);
    board[7][4] = createPiece(king, black, 7, 4);
    board[7][3] = createPiece(queen, black, 7, 3);
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = createPiece(empty, grey, j, i);
        }
    }
}

void setEmpty(PIECE * * *board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = createPiece(empty, grey, j, i);
        }
    }
}


void displayBoard(PIECE * * *board, COLOR side) {
    switch (side) {
        case white: {
            for (int i = 7; i >= 0; i--) {
                printf("%d  ", i + 1);
                for (int j = 0; j <8; j++) {
                    printf("%c", board[i][j]->symbole);
                }
                printf("\n");
            }
            printf("\n   abcdefgh\n");
            break;
        }
        case black: {
            for (int i = 0; i < 8; i++) {
                printf("%d  ", i + 1);
                for (int j = 0; j < 8; j++) {
                    printf("%c", board[i][j]->symbole);
                }
                printf("\n");
            }
            printf("\n   hgfedcba\n");
            break;
        }
        case grey: {
            printf("Error\n");
            break;
        }
    }
}

void displayBoardv2(PIECE ***board, COLOR side) {
    SetConsoleOutputCP(CP_UTF8);

    const char *columnsWhite = "    a   b   c   d   e   f   g   h\n";
    const char *columnsBlack = "    h   g   f   e   d   c   b   a\n";
    const char *topBorder = "  ╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n";
    const char *middleBorder = "  ╟───┼───┼───┼───┼───┼───┼───┼───╢\n";
    const char *bottomBorder = "  ╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n";

    const char *whiteSymbols[] = {
        [king] = "K", [queen] = "Q", [rook] = "R",
        [bishop] = "B", [knight] = "N", [pawn] = "P",
        [empty] = " "
    };

    const char *blackSymbols[] = {
        [king] = "k", [queen] = "q", [rook] = "r",
        [bishop] = "b", [knight] = "n", [pawn] = "p",
        [empty] = " "
    };

    const char *columns = (side == white) ? columnsWhite : columnsBlack;
    printf("%s%s", columns, topBorder);

    for (int i = (side == white ? 7 : 0); (side == white ? i >= 0 : i < 8); i += (side == white ? -1 : 1)) {
        printf("%d ║", i + 1);
        for (int j = (side == white ? 0 : 7); (side == white ? j < 8 : j >= 0); j += (side == white ? 1 : -1)) {
            PIECE *piece = board[i][j];
            const char *symbol = (piece->color == white) ? whiteSymbols[piece->type] : blackSymbols[piece->type];
            const char *separator = (j == (side == white ? 7 : 0)) ? "║" : "│";
            printf(" %s %s", symbol, separator);
        }
        printf("\n");
        if ((side == white && i > 0) || (side == black && i < 7)) {
            printf("%s", middleBorder);
        }
    }

    printf("%s%s", bottomBorder, columns);
}


void saveBoard(PIECE * * * board, char * fileName) {
    FILE * f = fopen(fileName, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char color;
            switch (board[i][j]->color) {
                case white: {
                    color = 'w';
                    break;
                }
                case black: {
                    color = 'b';
                    break;
                }
                case grey: {
                    color = 'g';
                    break;
                }
            }
            fprintf(f, "%c%c",board[i][j]->type, color);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

PIECE * * * loadBoard(char * fileName) {

    char buf[255];
    PIECE * * * board = createBoard();

    FILE * f = fopen(fileName, "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < 8; i++) {
        fgets(buf, 255, f);
        for (int j = 0; j < 8; j ++) {
            PIECE_TYPE type;
            COLOR color;
            switch (buf[j * 2]) {
                case 'P': {
                    type = pawn;
                    break;
                }
                case 'N': {
                    type = knight;
                    break;
                }
                case 'B': {
                    type = bishop;
                    break;
                }
                case 'R': {
                    type = rook;
                    break;
                }
                case 'Q': {
                    type = queen;
                    break;
                }
                case 'K': {
                    type = king;
                    break;
                }
                case '*': {
                    type = empty;
                    break;
                }
            }
            switch (buf[j * 2 + 1]) {
                case 'w': {
                    color = white;
                    break;
                }
                case 'b': {
                    color = black;
                    break;
                }
                case 'g': {
                    color = grey;
                    break;
                }
            }
            board[i][j] = createPiece(type, color, j, i);
        }
    }
    fclose(f);
    return board;
}


PIECE * * * copyBoard(PIECE * * * board) {
    PIECE * * * newBoard = createBoard();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            newBoard[i][j] = createPiece(board[i][j]->type, board[i][j]->color, j, i);
        }
    }
    return newBoard;
}


void deleteBoard(PIECE * * *board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            deletePiece(board[i][j]);
        }
    }
    free(board);
    board = NULL;
}