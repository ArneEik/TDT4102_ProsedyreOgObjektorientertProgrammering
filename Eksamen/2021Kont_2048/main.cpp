#include "Game_window.h"

int main() {

	constexpr int board_size = 4;
	constexpr int tile_size = 80;
	constexpr int win_value = 2048;
	const std::string window_title = "2048";

	Game_window game_window{board_size, win_value, tile_size, window_title};

	game_window.run();
	return 0;

}
