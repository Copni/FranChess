//
// Created by IamaU on 22/12/2023.
//
#include "piece.h"

PIECE * createPiece(PIECE_TYPE type, COLOR color){
    PIECE * p = (PIECE *) malloc(sizeof(PIECE));
    p->type = type;
    if(type == empty) {
        p->color = grey;
    } else {
        p->color = color;
    }
    switch(type) {
        case pawn: {
            if(color == white) {
                p->symbole = '♙';
            } else {
               p->symbole = '♟';
            }
            break;
        }
        case rook: {
            if(color == white) {
                p->symbole = '♖';
            } else {
                p->symbole = '♜';
            }
            break;
        }
        case knight: {
            if(color == white) {
                p->symbole = '♘';
            } else {
                p->symbole = '♞';
            }
            break;
        }case bishop: {
            if(color == white) {
                p->symbole = '♗';
            } else {
                p->symbole = '♝';
            }
            break;
        }
        case queen: {
            if(color == white) {
                p->symbole = '♕';
            } else {
                p->symbole = '♛';
            }
            break;
        }
        case king: {
            if(color == white) {
                p->symbole = '♔';
            } else {
                p->symbole = '♚';
            }
            break;
        }case empty: {
            p->symbole = ' ';
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
