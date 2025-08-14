//
// Created by IamaU on 14/04/2025.
//
#include "threat.h"

int isThreatened(const PIECE * p, PIECE ***board, COLOR color) {
    const COLOR opponentColor = (color == white) ? black : white;
    const int x = p->x;
    const int y = p->y;

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


PIECE * isPinned(PIECE * p, GAMESTATE * g){
    PIECE * king = (p->color == white) ? g->w_king : g->b_king;
    int xk = king->x, yk = king->y;
    int xp = p->x, yp = p->y;
    PIECE ***board = g->board;

    // Directions : {dx, dy, type1, type2}
    int directions[8][4] = {
        {1, 0, rook, queen},   // droite
        {-1, 0, rook, queen},  // gauche
        {0, 1, rook, queen},   // bas
        {0, -1, rook, queen},  // haut
        {1, 1, bishop, queen}, // bas droite
        {-1, 1, bishop, queen},// bas gauche
        {1, -1, bishop, queen},// haut droite
        {-1, -1, bishop, queen}// haut gauche
    };

    for(int d=0; d<8; d++){
        int dx = directions[d][0], dy = directions[d][1];
        int i = 1;
        int found_p = 0;
        int x = xk + dx, y = yk + dy;
        // Parcours depuis le roi
        while(x >= 0 && x < 8 && y >= 0 && y < 8){
            if(board[y][x]->type != empty){
                if(!found_p){
                    if(board[y][x] == p){
                        found_p = 1;
                    } else {
                        break; // autre pièce entre roi et p
                    }
                } else {
                    // Après p, vérifier pièce adverse
                    if(board[y][x]->color != p->color &&
                       (board[y][x]->type == directions[d][2] || board[y][x]->type == directions[d][3])){
                        return board[y][x];
                       }
                    break;
                }
            }
            x += dx;
            y += dy;
            i++;
        }
    }
    return NULL;
}


int * * getAttackedSquares(PIECE * * * board, COLOR color) {
    int * * matrice = malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++) {
        matrice[i] = malloc(8 * sizeof(int));
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isThreatened(board[i][j],board, color * -1) == 1) {
                matrice[i][j] = 1;
            } else {
                matrice[i][j] = 0;
            }
        }
    }
    return matrice;
}

/*
int isLegal(const char * move, GAMESTATE * gamestate, COLOR color) {
    if (move != "O-O" && move != "O-O-O") {
        findPawn()
    } else {
        switch (move) {
            case "O-O-O": // Long castle
                if (color == white && !gamestate->has_aw_rook_moved && !gamestate->has_w_king_moved && !gamestate->is_w_king_in_check && !isThreatened(gamestate->board[0][2], gamestate->board, black) && !isThreatened(gamestate->board[0][3], gamestate->board, black) && !isThreatened(gamestate->board[0][4], gamestate->board, black)) {
                    return 1;
                }
                if (color == black && !gamestate->has_ab_rook_moved && !gamestate->has_b_king_moved && !gamestate->is_b_king_in_check && !isThreatened(gamestate->board[7][2], gamestate->board, black) && !isThreatened(gamestate->board[7][3], gamestate->board, black) && !isThreatened(gamestate->board[7][4], gamestate->board, black)) {
                    return 1;
                }
                return 0;
            case "O-O": // Short castle
                if (color == white && !gamestate->has_hw_rook_moved && !gamestate->has_w_king_moved && !gamestate->is_w_king_in_check && !isThreatened(gamestate->board[0][4], gamestate->board, black) && !isThreatened(gamestate->board[0][5], gamestate->board, black) && !isThreatened(gamestate->board[0][6], gamestate->board, black)) {
                    return 1;
                }
                if (color == black && !gamestate->has_hb_rook_moved && !gamestate->has_b_king_moved && !gamestate->is_b_king_in_check && !isThreatened(gamestate->board[7][4], gamestate->board, white) && !isThreatened(gamestate->board[7][5], gamestate->board, white) && !isThreatened(gamestate->board[7][6], gamestate->board, white)) {
                    return 1;
                }
                return 0;
            default:
                break;
        }
    }


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

