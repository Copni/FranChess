cmake_minimum_required(VERSION 3.30)
project(AlgeChess C)

set(CMAKE_C_STANDARD 11)

add_executable(FranChess main.c
        board.h
        piece.c
        piece.h
        board.c
        findPiece.h
        findPiece.c
        move.h
        move.c
        threat.c
        threat.h
        gamestate.c
        gamestate.h
        displacement.h
        displacement.c
)
