#include <stdio.h>
#include "threat.h"
#include <assert.h>
#include "gamestate.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("Caractères Unicode : ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜\n");
    PIECE * * * newboard = createBoard();
    setBoard(newboard);
    PIECE * * * board1 = createBoard();
    setEmpty(board1);
    board1[0][0] = createPiece(queen, white);
    board1[4][5] = createPiece(rook, white);
    board1[3][6] = createPiece(rook, white);
    board1[0][5] = createPiece(rook, white);
    board1[3][0] = createPiece(king, white);
    board1[5][7] = createPiece(king, white);
    board1[1][1] = createPiece(king, white);
    board1[7][7] = createPiece(king, white);
    board1[7][1] = createPiece(knight, white);
    board1[6][0] = createPiece(knight, white);
    board1[0][1] = createPiece(knight, white);
    displayBoard(newboard,white);
    saveBoard(board1, "test.txt");
    PIECE * * * board2 = loadBoard("test.txt");


    GameState * g = init_board_data();
    display_board(g);

    return 0;
}
