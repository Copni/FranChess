//
// Created by IamaU on 22/12/2023.
//
#include "piece.h"

PIECE * createPiece(PIECE_TYPE type, COLOR color){
    PIECE * p = (PIECE *) malloc(sizeof(PIECE));
    p->type = type;
    if(type == empty) {
        p->color = grey;
        p->symbole = '*';
    } else {
        p->color = color;
    }
switch(type) {
    case pawn: {
        if(color == white) {
            p->symbole = 'P';
        } else {
            p->symbole = 'p';
        }
        break;
    }
    case rook: {
        if(color == white) {
            p->symbole = 'R';
        } else {
            p->symbole = 'r';
        }
        break;
    }
    case knight: {
        if(color == white) {
            p->symbole = 'N';
        } else {
            p->symbole = 'n';
        }
        break;
    }
    case bishop: {
        if(color == white) {
            p->symbole = 'B';
        } else {
            p->symbole = 'b';
        }
        break;
    }
    case queen: {
        if(color == white) {
            p->symbole = 'Q';
        } else {
            p->symbole = 'q';
        }
        break;
    }
    case king: {
        if(color == white) {
            p->symbole = 'K';
        } else {
            p->symbole = 'k';
        }
        break;
        }case empty: {
            p->symbole = '*';
            break;
        }
    }

    return p;
}

void printPiece(PIECE * piece) {
    char *typeStr;
    char *colorStr;

    switch (piece->type) {
        case pawn: typeStr = "Pawn"; break;
        case knight: typeStr = "Knight"; break;
        case bishop: typeStr = "Bishop"; break;
        case rook: typeStr = "Rook"; break;
        case queen: typeStr = "Queen"; break;
        case king: typeStr = "King"; break;
        case empty: typeStr = "Empty"; break;
    }

    switch (piece->color) {
        case white: colorStr = "White"; break;
        case black: colorStr = "Black"; break;
        case grey: colorStr = "Grey"; break;
    }

    printf("Piece information:\n    Type: %s\n    Color: %s\n", typeStr, colorStr);
}

void deletePiece(PIECE * p){
    free(p);
    p = NULL;
}