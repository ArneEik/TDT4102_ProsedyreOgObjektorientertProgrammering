#pragma once

#include <vector>
#include <map>
#include "Color.h"

enum class PlayerType { NONE, PLAYER_1, PLAYER_2 };

class Game {
public:
    Game(int rows = 6, int columns = 7);

    bool dropPiece(int column);
    bool checkWin() const;
    PlayerType currentPlayer() const;
    void switchPlayer();
    PlayerType getWinner() const;
    const std::vector<std::vector<PlayerType>>& getBoard() const;

private:
    std::vector<std::vector<PlayerType>> board;
    PlayerType currentPlayer_;
    PlayerType winner_;
    int rows, columns;

    bool isWinningMove(int row, int column) const;
    int countConsecutivePieces(int row, int col, int dRow, int dCol) const;
};
