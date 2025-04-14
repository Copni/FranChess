#include <stdio.h>
#include "threat.h"
#include <assert.h>
#include <windows.h>

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("Caractères Unicode : ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜\n");
    Color(15,0);
    printf("Hello, World!\n");
    printf("'1' - '0' = %d\n", '1' - '0');
    /*
    PIECE * * * board = createBoard();
    setBoard(board);
    displayBoard(board, white);

    printf("\nEntrez votre coup :");
    char * myMove = getMove();
    int i = 0;
    printf("\nMy move = %s \n", myMove);
    for(int i = 0; i < length(myMove); i++) {
        printf("%c", myMove[i]);
    }
    printf("\n");


    displayBoard(loadBoard("board.txt"),white)  ;
    deleteBoard(board);
    */
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
    displayBoardv2(newboard,white);
    saveBoard(board1, "test.txt");
    PIECE * * * board2 = loadBoard("test.txt");




    // Cas 1 : Case non menacée
    assert(isThreatened(0, 0, board2, black) == 1);

    // Cas 2 : Case menacée par une pièce noire
    assert(isThreatened(3, 6, board2, black) == 1);

    // Cas 3 : Case menacée par une pièce blanche
    assert(isThreatened(3, 6, board2, white) == 0);

    // Cas 4 : Case non menacée par une pièce blanche
    assert(isThreatened(7, 7, board2, white) == 0);

    // Cas 5 : Case menacée par un cavalier blanc
    assert(isThreatened(2, 2, board2, black) == 1);

    // Cas 6 : Case menacée par une reine blanche
    assert(isThreatened(0, 7, board2, black) == 1);

    // Cas 7 : Case non menacée par une pièce noire
    assert(isThreatened(4, 4, board2, black) == 0);

    // Cas 8 : Case menacée par un roi blanc
    assert(isThreatened(4, 3, board2, black) == 1);

    printf("Tous les tests sont passés avec succès.\n");
    /*
    printf("\nEnter a move:");
    char *  myMove = getMove();
    printf("My move = %s \n", myMove);

    int * * pieceList = findKnight(myMove, board2, white);
    int i = 0;
    while (pieceList[i] != NULL) {
        printf("Knight %d: %c%d\n", i + 1, pieceList[i][0] + 'a', pieceList[i][1] + 1);
        i++;
    }
    */

    /*
    char move[5];
    fgets(move,6,stdin);
    char * test = "e4";
    if (same_string(move, test) == 1){
        printf("test concluant");
    }
    else{
        printf("error");
    }
    printf(" \nTest:\0ok");
    */

    /*
    printf("\n>>>");
    MOVE * p = get_move();
    if(p != NULL){
        printf("Correct !");
    }
    else{
        printf("Incorrect !");
    }
    printf("\nSo far so good !\n");
    */
    return 0;
}
