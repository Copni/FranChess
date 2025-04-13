//
// Created by IamaU on 07/11/2024.
//
#include "legal.h"

/* the input move is converted in a fixed string:
Index 0: piece type
Index 1: complementary line or row index
Index 2: 'x' if a piece is eaten
Index 3: row index
Index 4: line index
Index 5: promoted piece type
Index 6: '+' or '#' if check or mat
Everything is '0' by default
*/

void addElement(int ***foundPiece, int *pieceCount, int x, int y) {
    *foundPiece = (int **)realloc(*foundPiece, (*pieceCount + 1) * sizeof(int *));
    (*foundPiece)[*pieceCount] = (int *)malloc(2 * sizeof(int));
    (*foundPiece)[*pieceCount][0] = x;
    (*foundPiece)[*pieceCount][1] = y;
    (*pieceCount)++;
}

void removeElement(int ***array, int *size, int index) {
    if (index < 0 || index >= *size) {
        return;
    }

    // Libérer la mémoire de la case à supprimer
    free((*array)[index]);

    // Décaler les éléments suivants vers la gauche
    for (int i = index; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }

    // Réallocation pour réduire la taille du tableau
    int **temp = realloc(*array, (*size - 1) * sizeof(int *));
    if (temp != NULL || *size - 1 == 0) {  // Vérifie si realloc a réussi
        *array = temp;
        (*size)--;
    } else {
        printf("Error while reallocating memory\n");
    }
}

int **findPawn(char *move, PIECE ***board, COLOR color) {
    int const x = move[3] - 'a';
    int const y = move[4] - '0' - 1;

    int **foundPawn = NULL;
    int pawnCount = 0;

    switch (color) {
        case white:
            if (y < 2) {
                return NULL;
            }

            // Normal one-step move
            if (board[y - 1][x]->type == pawn && board[y - 1][x]->color == white && move[2] == '0') {
                addElement(&foundPawn, &pawnCount, x, y - 1);
            }

            // Two-step move from starting position
            if (y == 3 && board[y - 2][x]->type == pawn && board[y - 2][x]->color == white && move[2] == '0' &&
                board[y - 1][x]->type == empty) {
                addElement(&foundPawn, &pawnCount, x, y - 2);
            }

            // Capture moves
            if (move[2] == 'x') {
                if (x < 7 && board[y - 1][x + 1]->type == pawn && board[y - 1][x + 1]->color == white) {
                    addElement(&foundPawn, &pawnCount, x + 1, y - 1);
                }
                if (x > 0 && board[y - 1][x - 1]->type == pawn && board[y - 1][x - 1]->color == white) {
                    addElement(&foundPawn, &pawnCount, x - 1, y - 1);
                }
            }
            break;

        case black:
            if (y > 5) {
                return NULL;
            }

            // Normal one-step move
            if (board[y + 1][x]->type == pawn && board[y + 1][x]->color == black && move[2] == '0') {
                addElement(&foundPawn, &pawnCount, x, y + 1);
            }

            // Two-step move from starting position
            if (y == 4 && board[y + 2][x]->type == pawn && board[y + 2][x]->color == black && move[2] == '0' &&
                board[y + 1][x]->type == empty) {
                addElement(&foundPawn, &pawnCount, x, y + 2);
            }

            // Capture moves
            if (move[2] == 'x') {
                if (x < 7 && board[y + 1][x + 1]->type == pawn && board[y + 1][x + 1]->color == black) {
                    addElement(&foundPawn, &pawnCount, x + 1, y + 1);
                }
                if (x > 0 && board[y + 1][x - 1]->type == pawn && board[y + 1][x - 1]->color == black) {
                    addElement(&foundPawn, &pawnCount, x - 1, y + 1);
                }
            }
            break;

        default:
            return NULL;
    }

    // Add sentinel NULL to signal end of array
    foundPawn = (int **)realloc(foundPawn, (pawnCount + 1) * sizeof(int *));
    foundPawn[pawnCount] = NULL;

    return foundPawn;
}

int **findKnight(char *move, PIECE ***board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    int **foundKnight = NULL;
    int knightCount = 0;

    // Possible moves for a knight
    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int i = 0; i < 8; i++) {
        int n = y + directions[i][0];
        int m = x + directions[i][1];
        if (n >= 0 && n < 8 && m >= 0 && m < 8) {
            if (board[n][m]->type == knight && board[n][m]->color == color) {
                addElement(&foundKnight, &knightCount, m, n);
            }
        }
    }

    // Add sentinel NULL to signal end of array
    foundKnight = (int **)realloc(foundKnight, (knightCount + 1) * sizeof(int *));
    foundKnight[knightCount] = NULL;

    return foundKnight;
}

int **findBishop(char *move, PIECE ***board, COLOR color) {
        int x = move[3] - 'a';
        int y = move[4] - '0' - 1;

        int **foundBishop = NULL;
        int bishopCount = 0;

        // Check diagonals for bishops
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (int i = 0; i < 4; i++) {
            int n = y + directions[i][0];
            int m = x + directions[i][1];
            while (n >= 0 && n < 8 && m >= 0 && m < 8) {
                if (board[n][m]->type == empty) {
                    n += directions[i][0];
                    m += directions[i][1];
                } else {
                    if (board[n][m]->type == bishop && board[n][m]->color == color) {
                        addElement(&foundBishop, &bishopCount, m, n);
                    }
                    break;
                }
            }
        }

        // Add sentinel NULL to signal end of array
        foundBishop = (int **)realloc(foundBishop, (bishopCount + 1) * sizeof(int *));
        foundBishop[bishopCount] = NULL;

        return foundBishop;
    }

    int **findRook(char *move, PIECE ***board, COLOR color) {
        int x = move[3] - 'a';
        int y = move[4] - '0' - 1;

        int **foundRook = NULL;
        int rookCount = 0;

        // Check straight lines for rooks
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < 4; i++) {
            int n = y + directions[i][0];
            int m = x + directions[i][1];
            while (n >= 0 && n < 8 && m >= 0 && m < 8) {
                if (board[n][m]->type == empty) {
                    n += directions[i][0];
                    m += directions[i][1];
                } else {
                    if (board[n][m]->type == rook && board[n][m]->color == color) {
                        addElement(&foundRook, &rookCount, m, n);
                    }
                    break;
                }
            }
        }

        // Add sentinel NULL to signal end of array
        foundRook = (int **)realloc(foundRook, (rookCount + 1) * sizeof(int *));
        foundRook[rookCount] = NULL;

        return foundRook;
    }

int **findQueen(char *move, PIECE ***board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    int **foundQueen = NULL;
    int queenCount = 0;
    int n, m;

    // Check diagonals and straight lines for queens
    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 8; i++) {
        n = y + directions[i][0];
        m = x + directions[i][1];
        while (n >= 0 && n < 8 && m >= 0 && m < 8) {
            if (board[n][m]->type == empty) {
                n += directions[i][0];
                m += directions[i][1];
            } else {
                if (board[n][m]->type == queen && board[n][m]->color == color) {
                    addElement(&foundQueen, &queenCount, m, n);
                }
                break;
            }
        }
    }

    // Add sentinel NULL to signal end of array
    foundQueen = (int **)realloc(foundQueen, (queenCount + 1) * sizeof(int *));
    foundQueen[queenCount] = NULL;

    return foundQueen;
}


int **findKing(char *move, PIECE ***board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    int **foundKing = NULL;
    int kingCount = 0;
    int n, m;

    // Check surrounding squares for king
    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 8; i++) {
        n = y + directions[i][0];
        m = x + directions[i][1];
        if (n >= 0 && n < 8 && m >= 0 && m < 8) {
            if (board[n][m]->type == king && board[n][m]->color == color) {
                addElement(&foundKing, &kingCount, m, n);
            }
        }
    }

    // Add sentinel NULL to signal end of array
    foundKing = (int **)realloc(foundKing, (kingCount + 1) * sizeof(int *));
    foundKing[kingCount] = NULL;

    return foundKing;
}


int isThreatened(int x, int y, PIECE ***board, COLOR color) {
    COLOR opponentColor = (color == white) ? black : white;

    // Check for pawns
    if (color == white) {
        if (x > 0 && y < 7 && board[y + 1][x - 1]->type == pawn && board[y + 1][x - 1]->color == black) return 1;
        if (x < 7 && y < 7 && board[y + 1][x + 1]->type == pawn && board[y + 1][x + 1]->color == black) return 1;
    } else {
        if (x > 0 && y > 0 && board[y - 1][x - 1]->type == pawn && board[y - 1][x - 1]->color == white) return 1;
        if (x < 7 && y > 0 && board[y - 1][x + 1]->type == pawn && board[y - 1][x + 1]->color == white) return 1;
    }

    // Check for knights
    int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int i = 0; i < 8; i++) {
        int nx = x + knightMoves[i][0];
        int ny = y + knightMoves[i][1];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && board[ny][nx]->type == knight && board[ny][nx]->color == opponentColor) {
            return 1;
        }
    }

    // Check for bishops and queens (diagonals)
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            if (board[ny][nx]->type != empty) {
                if ((board[ny][nx]->type == bishop || board[ny][nx]->type == queen) && board[ny][nx]->color == opponentColor) {
                    return 1;
                }
                break;
            }
            nx += directions[i][0];
            ny += directions[i][1];
        }
    }

    // Check for rooks and queens (straight lines)
    int straightDirections[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int nx = x + straightDirections[i][0];
        int ny = y + straightDirections[i][1];
        while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            if (board[ny][nx]->type != empty) {
                if ((board[ny][nx]->type == rook || board[ny][nx]->type == queen) && board[ny][nx]->color == opponentColor) {
                    return 1;
                }
                break;
            }
            nx += straightDirections[i][0];
            ny += straightDirections[i][1];
        }
    }

    // Check for kings
    int kingMoves[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 8; i++) {
        int nx = x + kingMoves[i][0];
        int ny = y + kingMoves[i][1];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && board[ny][nx]->type == king && board[ny][nx]->color == opponentColor) {
            return 1;
        }
    }

    return 0;
}

int isPinned(PIECE **pinnedPiece, PIECE **target, PIECE ***board, COLOR color) {
    int x1 = pinnedPiece[0] - board[0];
    int y1 = pinnedPiece[1] - board[0];
    int x2 = target[0] - board[0];
    int y2 = target[1] - board[0];

    // Check if the pinned piece is in the same row, column, or diagonal as the target
    if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2)) {
        int dx = (x2 - x1) ? (x2 - x1) / abs(x2 - x1) : 0;
        int dy = (y2 - y1) ? (y2 - y1) / abs(y2 - y1) : 0;

        int x = x1 + dx;
        int y = y1 + dy;
        while (x != x2 || y != y2) {
            if (board[y][x]->type != empty) {
                if (board[y][x] == target) {
                    x += dx;
                    y += dy;
                    while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                        if (board[y][x]->type != empty) {
                            if (board[y][x]->color != color &&
                                (board[y][x]->type == rook || board[y][x]->type == bishop || board[y][x]->type == queen)) {
                                return 1;
                            }
                            break;
                        }
                        x += dx;
                        y += dy;
                    }
                }
                break;
            }
            x += dx;
            y += dy;
        }
    }
    return 0;
}
/*
int * isMovePossible (char * move, PIECE * * * board, COLOR color) {
    int * * foundPieceList = findRook(move, board, color);

    int found = 0;
    while (foundPieceList[found] != NULL) {
        found++;
    }

    if(found == 0){
        free(foundPieceList);
        return NULL;
    }

    if(found == 1 && move[1] == '0'){
        int *result = foundPieceList[0];
        free(foundPieceList);
        foundPieceList = NULL;
        return result;
    }

    if (found > 1 && move[1] != '0') {
        int i = 0;
        if (move[1] >= 'a' && move[1] <= 'h') {
            while (foundPieceList[i] != NULL) {
                if (foundPieceList[i][0] != move[1] - 'a') {
                    removeElement(foundPieceList, &found, i);
                }else {
                    i++;
                }
            }
        } else if (move[1] >= '1' && move[1] <= '8') {
            while (foundPieceList[i] != NULL) {
                if (foundPieceList[i][1] != move[1] - '0' - 1) {
                    removeElement(foundPieceList, &found, i);
                }else {
                    i++;
                }
            }
        }
    }

    if (found == 1) {
        int *result = foundPieceList[0];
        free(foundPieceList);
        foundPieceList = NULL;
        return result;
    }

    return NULL;
}




/*
PIECE * isPawnLegal(char * move, PIECE * * *board, COLOR color) {
    int const x = move[3] - '0';
    int const y = move[4];

    // clasique move
    if (move[2] == '0' && board[x][y]->type == empty && (
        // ajouter la fonction en fonction du +2 selon couleur
            (board[x][y - 1]->type == empty && board[x][y - 1]->color == color && board[x][y - 2]->type == pawn && y-2 == 2 || (
                board[x][y - 1]->type == pawn && board[x][y - 1]->color == color)){
        return board[x][y];
    }

    return NULL;

    /*
    if (move[2] == 'x' && board[move[3]][move[4]]->color == color * -1) {
        if (move[1] != '0') {
            if (move[3] == 'a' && board[move]) {
            }
        }
    } else {
        if (board[move[3]][move[4 - 1]]->type == pawn && board[move[3]][move[4 - 1]]->color == color && board[move[3]][
                move[4]]->type == empty) {
            return "%c%c", move[3], move[4];
        }
    }
}
*/

/*
int is_legal(MOVE * move, SQUARE * * * board, COLOR color){
    SQUARE * s1, s2;
    switch(move->piece_type){
        case pawn:{
            case
            break;
        }
        case rook:{
            for(int i = move->pos_y; i < 8; i++){
                if(board[i][move->pos_x]->type == rook){ // utiliser while

                }
            }
            break;
        }
        case knight:{
            break;
        }
        case bishop:{
            break;
        }
        case king:{
            break;
        }
        case queen:{
            break;
        }
    }
}
*/
