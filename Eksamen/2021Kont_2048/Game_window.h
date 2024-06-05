#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Game.h"
#include "Tile.h"

class Game_window : public TDT4102::AnimationWindow {
  public:
	Game_window(int board_size, int win_value, int tile_size, const std::string& title);
	void run();
	bool lastStateR = false;

  private:
	// Modify the board
	void reset();
	void update();
	void update_tiles();
	void update_tile(int x, int y, int value);

	// Capture key presses and pass to action functions
	void handleInput();
	// void handle_arrow_key(KeyboardKey k);

	// For debugging under the exam
	void insert_two_tiles();
	void insert_increasing_tiles();
	void insert_push_merge_tiles();
	void debug_transpose_tiles();
	void debug_flip_tiles();
	void debug_update();

	// Misc
	void check_status();
	void reset_or_quit(const std::string& text);
	void hide_tiles();
	void cb_quit();
	void cb_reset();

	Game game;
	int board_size;
	int tile_s;
	std::vector<std::vector<std::unique_ptr<Tile>>> graphical_tiles;
	TDT4102::Button quitBtn;
	TDT4102::Button resetBtn;
};