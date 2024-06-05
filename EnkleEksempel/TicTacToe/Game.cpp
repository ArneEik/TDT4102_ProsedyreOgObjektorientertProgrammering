#include "Game.h"

// Konstruktør
Game::Game(int rows, int columns)
    : rows(rows), columns(columns), currentPlayer_(PlayerType::PLAYER_1), winner_(PlayerType::NONE) {
    board.resize(rows, std::vector<PlayerType>(columns, PlayerType::NONE));
}

// Slippe brikke
bool Game::dropPiece(int column) {
    if (column < 0 || column >= columns) return false;
    for (int row = rows - 1; row >= 0; --row) {
        if (board[row][column] == PlayerType::NONE) {
            board[row][column] = currentPlayer_;
            if (isWinningMove(row, column)) {
                winner_ = currentPlayer_;
            }
            switchPlayer();
            return true;
        }
    }
    return false;
}

// Sjekk om noen har vunnet
bool Game::checkWin() const {
    return winner_ != PlayerType::NONE;
}

// Returner nåværende spiller
PlayerType Game::currentPlayer() const {
    return currentPlayer_;
}

// Bytt spiller
void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == PlayerType::PLAYER_1) ? PlayerType::PLAYER_2 : PlayerType::PLAYER_1;
}

// Returner vinner
PlayerType Game::getWinner() const {
    return winner_;
}

// Returner brettet
const std::vector<std::vector<PlayerType>>& Game::getBoard() const {
    return board;
}

// Sjekk om flytting er vinnende
bool Game::isWinningMove(int row, int column) const {
    PlayerType player = board[row][column];
    return countConsecutivePieces(row, column, 1, 0) >= 4 || // Horisontal
           countConsecutivePieces(row, column, 0, 1) >= 4 || // Vertikal
           countConsecutivePieces(row, column, 1, 1) >= 4 || // Diagonal oppover
           countConsecutivePieces(row, column, 1, -1) >= 4;  // Diagonal nedover
}

// Telle antall på rad
int Game::countConsecutivePieces(int row, int col, int dRow, int dCol) const {
    int count = 0;
    PlayerType player = board[row][col];
    for (int i = -3; i <= 3; ++i) {
        int newRow = row + i * dRow;
        int newCol = col + i * dCol;
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && board[newRow][newCol] == player) {
            ++count;
            if (count == 4) {
                return count;
            }
        } else {
            count = 0;
        }
    }
    return count;
}
