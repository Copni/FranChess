#include <stdio.h>
#include "threat.h"
#include <assert.h>

#include <windows.h>


int main() {
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




    return 0;
}
