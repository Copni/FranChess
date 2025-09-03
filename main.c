#include <stdio.h>
#include "threat.h"
#include "displacement.h"


int main() {
    /*
    SetConsoleOutputCP(CP_UTF8);
    printf("Caractères Unicode : ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜\n");
    PIECE * * * newboard = createBoard();
    setBoard(newboard);
    PIECE * * * board1 = createBoard();
    setEmpty(board1);
    board1[0][0] = createPiece(king, white);
    board1[0][5] = createPiece(knight, white);
    board1[5][0] = createPiece(knight, white);
    board1[0][7] = createPiece(rook, black);
    board1[7][0] = createPiece(queen, black);
    board1[5][5] = createPiece(knight, white);
    board1[7][7] = createPiece(bishop, black);
    board1[3][3] = createPiece(pawn, black);
    displayBoard(newboard,white);
    displayBoardv2(newboard,white);





    saveBoard(board1, "test.txt");
    PIECE * * * board2 = loadBoard("test.txt");
    displayBoardv2(board2, white);

    GAMESTATE * g = gen_board_data(board1);
    if (isPinned(board1[0][5], g) != NULL) {
        printf("La pièce est clouée.\n");
    } else {
        printf("La pièce n'est pas clouée.\n");
    }
    if (isPinned(board1[5][5], g) != NULL) {
        printf("La pièce est clouée.\n");
    } else {
        printf("La pièce n'est pas clouée.\n");
    }
    if (isPinned(board1[5][0], g) != NULL) {
        printf("La pièce est clouée.\n");
    } else {
        printf("La pièce n'est pas clouée.\n");
    }

    */


    // Supposons que les prototypes suivants existent dans findpiece.c
    // PIECE *findKing(PIECE ***board, COLOR color);
    // PIECE *findRook(PIECE ***board, COLOR color, int rookIndex);
    // PIECE *findPiece(PIECE ***board, TYPE type, COLOR color);
    /*
    PIECE ***board = createBoard();
    setBoard(board); // Position initiale
    displayBoardv2(board,white);
    */
    GAMESTATE *g = init_board_data();
    setEmpty(g->board);

    g->board[7][4] = createPiece(king, black, 4, 7);
    g->board[7][7] = createPiece(rook, black, 7, 7);
    g->board[7][0] = createPiece(rook, black, 0, 7);

    MOVE *M = (MOVE *) malloc(sizeof(MOVE));
    M->move = NULL;
    M->type = long_castle;
    executeMove(g, M, black);

    displayBoardv2(g->board, white);


    MOVE *move = getMove();
    PIECE *p = findPiece(move, g->board, black);

    printPiece(p);


    return 0;
}
