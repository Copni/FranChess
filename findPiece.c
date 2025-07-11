//
// Created by IamaU on 07/11/2024.
//
#include "findPiece.h"

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


/*
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

int **findPawn(const char *move, PIECE ***board, COLOR color) {
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

int **findKnight(const char *move, PIECE ***board, COLOR color) {
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

int **findBishop(const char *move, PIECE ***board, COLOR color) {
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

    int **findRook(const char *move, PIECE ***board, COLOR color) {
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

int **findQueen(const char *move, PIECE ***board, COLOR color) {
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


int **findKing(const char *move, PIECE ***board, COLOR color) {
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


int * * findPiece(char * move, PIECE * * * board, COLOR color) {
    switch (move[0]) {
        case 'P':
            return findPawn(move, board, color);
        case 'N':
            return findKnight(move, board, color);
        case 'B':
            return findBishop(move, board, color);
        case 'R':
            return findRook(move, board, color);
        case 'Q':
            return findQueen(move, board, color);
        case 'K':
            return findKing(move, board, color);
        default:
            return NULL;
    }
}
*/


//
// Created by IamaU on 07/11/2024.
//

#include "findPiece.h"
#include <stdlib.h>
#include <stdio.h>

void addPiece(PIECE ***foundPieces, int *count, PIECE *piece) {
    *foundPieces = realloc(*foundPieces, (*count + 1) * sizeof(PIECE *));
    (*foundPieces)[*count] = piece;
    (*count)++;
}

PIECE * * findPawn(const char * move, PIECE * * * board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    if (color == white) {
        if (y >= 1 && board[y - 1][x]->type == pawn && board[y - 1][x]->color == white && move[2] == '0')
            addPiece(&found, &count, board[y - 1][x]);
        if (y == 3 && board[y - 2][x]->type == pawn && board[y - 2][x]->color == white &&
            board[y - 1][x]->type == empty && move[2] == '0')
            addPiece(&found, &count, board[y - 2][x]);
        if (move[2] == 'x') {
            if (x < 7 && board[y - 1][x + 1]->type == pawn && board[y - 1][x + 1]->color == white)
                addPiece(&found, &count, board[y - 1][x + 1]);
            if (x > 0 && board[y - 1][x - 1]->type == pawn && board[y - 1][x - 1]->color == white)
                addPiece(&found, &count, board[y - 1][x - 1]);
        }
    } else {
        if (y <= 6 && board[y + 1][x]->type == pawn && board[y + 1][x]->color == black && move[2] == '0')
            addPiece(&found, &count, board[y + 1][x]);
        if (y == 4 && board[y + 2][x]->type == pawn && board[y + 2][x]->color == black &&
            board[y + 1][x]->type == empty && move[2] == '0')
            addPiece(&found, &count, board[y + 2][x]);
        if (move[2] == 'x') {
            if (x < 7 && board[y + 1][x + 1]->type == pawn && board[y + 1][x + 1]->color == black)
                addPiece(&found, &count, board[y + 1][x + 1]);
            if (x > 0 && board[y + 1][x - 1]->type == pawn && board[y + 1][x - 1]->color == black)
                addPiece(&found, &count, board[y + 1][x - 1]);
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findKnight(const char * move, PIECE * * * board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        if (ny >= 0 && ny < 8 && nx >= 0 && nx < 8) {
            if (board[ny][nx]->type == knight && board[ny][nx]->color == color) {
                addPiece(&found, &count, board[ny][nx]);
            }
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findBishop(const char * move, PIECE * * * board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < 4; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        while (ny >= 0 && ny < 8 && nx >= 0 && nx < 8) {
            if (board[ny][nx]->type == empty) {
                ny += directions[i][0];
                nx += directions[i][1];
            } else {
                if (board[ny][nx]->type == bishop && board[ny][nx]->color == color) {
                    addPiece(&found, &count, board[ny][nx]);
                }
                break;
            }
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findRook(const char *move, PIECE ***board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        while (ny >= 0 && ny < 8 && nx >= 0 && nx < 8) {
            if (board[ny][nx]->type == empty) {
                ny += directions[i][0];
                nx += directions[i][1];
            } else {
                if (board[ny][nx]->type == rook && board[ny][nx]->color == color) {
                    addPiece(&found, &count, board[ny][nx]);
                }
                break;
            }
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findQueen(const char *move, PIECE ***board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
                            {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        while (ny >= 0 && ny < 8 && nx >= 0 && nx < 8) {
            if (board[ny][nx]->type == empty) {
                ny += directions[i][0];
                nx += directions[i][1];
            } else {
                if (board[ny][nx]->type == queen && board[ny][nx]->color == color) {
                    addPiece(&found, &count, board[ny][nx]);
                }
                break;
            }
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findKing(const char * move, PIECE * * * board, COLOR color) {
    int x = move[3] - 'a';
    int y = move[4] - '0' - 1;
    PIECE * * found = NULL;
    int count = 0;

    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
                            {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 8; i++) {
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];
        if (ny >= 0 && ny < 8 && nx >= 0 && nx < 8) {
            if (board[ny][nx]->type == king && board[ny][nx]->color == color) {
                addPiece(&found, &count, board[ny][nx]);
            }
        }
    }

    found = realloc(found, (count + 1) * sizeof(PIECE *));
    found[count] = NULL;
    return found;
}

PIECE * * findPiece(char * move, PIECE * * * board, COLOR color) {
    switch (move[0]) {
        case 'P': return findPawn(move, board, color);
        case 'N': return findKnight(move, board, color);
        case 'B': return findBishop(move, board, color);
        case 'R': return findRook(move, board, color);
        case 'Q': return findQueen(move, board, color);
        case 'K': return findKing(move, board, color);
        default: return NULL;
    }
}
