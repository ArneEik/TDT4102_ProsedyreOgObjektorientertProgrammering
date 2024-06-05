#pragma once

#include "AnimationWindow.h"
#include "Board.h"
#include "BoardGame.h"
#include "widgets/DropdownList.h"
#include <filesystem>

extern std::unique_ptr<TDT4102::DropdownList> list;
extern std::unique_ptr<BoardGame> game_ptr;

/**
 * Returns a player key based on the passed player.
 *
 * @return The player's string representation
 */
std::string player_key(Player player);

/**
 * Returns the number of chips left on the board for both players.
 *
 * @return A pair of counts. The first for player one, the second for player two.
 */
std::pair<int,int> count_chips(std::vector<Tile> cells);


void draw_default_chip(TDT4102::AnimationWindow &window, TDT4102::Point anchor,
                       Player player, int width, int height);


void reset_button_callback();

Board load_board(const std::filesystem::path &path);

bool is_valid_direction(TDT4102::Point from, TDT4102::Point to, Player player);

// ============================================================
// ============================================================
bool points_equal(TDT4102::Point p1, TDT4102::Point p2);
bool equality_operator_presence_point();
std::string extension_to_lower(const std::string &from);


