#pragma once

#include <vector>
#include "AnimationWindow.h"

/**
 * Enum class that signifies a player
 */
enum class Player {
    NONE,
    ONE,
    TWO
};

/**
 * A tile on the board
 */
struct Tile {

    //! The player occupying the tile.
    Player player;

    //! `true` when it's the occupying piece's first move.
    bool firstMove{false};
};



struct Board {

    Board(int size_);
    Board();

    Board(const Board &other) = default;
    Board &operator=(const Board &other) = default;

    //! Creates a new board with pieces set to their correct positions.
    static Board create_blank(int size_);

    //! Get the size n of the board (n x n)
    int get_size() const;

    //! Move a piece from `from` to `to`
    void move(TDT4102::Point from, TDT4102::Point to);

    //! Get a reference to the cell at (x, y)
    Tile &cell_at(int x, int y);

    //! Get a reference to the cell at (x, y)
    const Tile &cell_at(int x, int y) const;

    //! Get a constant reference to the tile storage
    std::vector<Tile> const &get_cells() const;

  private:
    int size;
    std::vector<Tile> cells;
};



