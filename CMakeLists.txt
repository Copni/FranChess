cmake_minimum_required(VERSION 3.30)
project(AlgeChess C)

set(CMAKE_C_STANDARD 11)

add_executable(FranChess main.c
        board.h
        piece.c
        piece.h
        board.c
        legal.h
        legal.c
        move.h
        move.c)
