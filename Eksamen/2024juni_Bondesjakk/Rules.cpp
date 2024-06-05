#include "Board.h"
#include "Rules.h"
#include "RuleUtils.h"
#include "Tasks.h"

bool Rules::can_move(Board &board, TDT4102::Point from, TDT4102::Point to,
                               Player turn) {

  auto [x1, y1] = from;
  auto size = board.get_size();

  auto [x2, y2] = to;

  // Fail if any of the selected points lie outside the board
  if (   x1 >= size  || x1 < 0
      || y1 >= size  || y1 < 0
      || x2 >= size || x2 < 0
      || y2 >= size || y2 < 0)
    return false;

  bool diagonal = RuleUtils::isDiagonal(from, to);
  auto distance = RuleUtils::distance(from, to);
  auto diff = RuleUtils::diff(from, to);
  bool validDirection = is_valid_direction(from, to, turn);

  bool selectedValid = board.cell_at(x1, y1).player == turn;

  bool distanceCondition = false;
  if (board.cell_at(x1, y1).firstMove) {
    distanceCondition = distance <= 2 && diff.x == 0;

    // If there is a player between, the move is not valid.
    if ( distance == 2 ) {
        distanceCondition &= board.cell_at(from.x, from.y + diff.y / 2).player == Player::NONE;
    }
  } else {
    distanceCondition = distance == 1;
  }


  bool earlyFailure = !distanceCondition || !selectedValid || !validDirection;

  if (earlyFailure)
    return false;

  auto playerOnCell = board.cell_at(x2, y2).player;

  // If the move is diagonal, it must be to capture another player's pawn
  if (diagonal) {
    return playerOnCell != Player::NONE && playerOnCell != turn;
  } else {
    // Otherwise, we can only move into an uninhabited tile.
    return playerOnCell == Player::NONE;
  }
}

Player Rules::winner(Board &board) {
  // If player two on top rows, two wins
  int size = board.get_size();

  for (int x = 0; x < size; x++) {
    if (board.cell_at(x, 0).player == Player::TWO) {
      return Player::TWO;
    }

    if (board.cell_at(x, size - 1).player == Player::ONE) {
      return Player::ONE;
    }
  }

  return Player::NONE;
}

bool Rules::move(Board &board, TDT4102::Point from, TDT4102::Point to,
                            Player turn) {
  bool validMove = can_move(board, from, to, turn);

  board.move(from, to);

  board.cell_at(from.x, from.y).firstMove = false;

  return validMove;
}
