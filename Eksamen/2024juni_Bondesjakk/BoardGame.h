#pragma once

#include "Board.h"
#include "Entity.h"

struct BoardGame : public Entity {

  BoardGame(int size);
  BoardGame(const Board &board_);

  /// Get the current player.
  Player get_current_player() const;

  /// Get the current player.
  Player get_winner() const;

  /// The current user-selected tile.
  TDT4102::Point selected{-1, -1};

  /// Get the vector of highlighted tiles for the renderer.
  const std::vector<bool> &get_highlighted() const;

  /// Interactive interface. Performs the game logic.
  /// Returns true if a user's interaction yielded a change in the game state.
  bool interact(TDT4102::Point pt);

  bool inside_interaction_zone(TDT4102::Point pt);

  /// Resets and resizes the highlighted vector
  void resize(int size);

  /// Set to true when the game is interactive / still ongoing.
  bool enabled = true;

  // The board in use by the game
  Board board;


private:
  /// Maintains the set of tiles that should be highlighted by the renderer.
  std::vector<bool> highlighted;

  /// The player that has won. Set to Player::NONE when no winner.
  Player winner = Player::NONE;

  /// The player whose turn it is to make a move.
  Player turn;

  /// A routine that highlights the valid moves for a given selected tile.
  void highlight();

  void unselect();

  void end_turn();

};


