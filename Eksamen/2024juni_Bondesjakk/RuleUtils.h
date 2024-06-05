#pragma once


#include "Board.h"
#include "Entity.h"

struct RuleUtils {

    /// Returns the "normalized" direction vector.
    static inline TDT4102::Point direction(TDT4102::Point from, TDT4102::Point to)
    {

        auto diff = RuleUtils::diff(from, to);

        auto [dx, dy] = diff;

        if (dx == 0 || dy == 0 ) {
            return {0,0};
        }

        return {dx / std::abs(dx), dy / std::abs(dy) };
    }

    static inline TDT4102::Point diff(TDT4102::Point from, TDT4102::Point to)
    {
        return {to.x - from.x, to.y - from.y};
    }

    static bool isDiagonal(TDT4102::Point from, TDT4102::Point to)
    {
        auto [dx, dy] = diff(from, to);
        return (dx != 0) && (std::abs(dx) == std::abs(dy));
    }

    static int distance(TDT4102::Point from, TDT4102::Point to)
    {
        auto [dx, dy] = diff(from, to);

        return std::max( std::abs(dx), std::abs(dy) );
    }

    static bool isValidDirection(TDT4102::Point from, TDT4102::Point to, Player player)
    {
        return true;
    }




};



