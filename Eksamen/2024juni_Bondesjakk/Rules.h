#pragma once


#include "Board.h"

struct Rules {

    static bool can_move(Board &board, TDT4102::Point from, TDT4102::Point to,
            Player turn);

    static bool move(Board &board, TDT4102::Point from, TDT4102::Point to,
            Player turn);


    static Player winner(Board &board);
};



