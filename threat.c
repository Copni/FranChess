//
// Created by IamaU on 14/04/2025.
//
#include "threat.h"

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

/*
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

