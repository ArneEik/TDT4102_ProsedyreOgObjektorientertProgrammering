#include "Game_window.h"


// The game window spawns at the center of the screen
Game_window::Game_window(int board_size,
                         int win_value,
                         int tile_size,
                         const std::string& title)
	: AnimationWindow(board_size * tile_size,  
			 board_size * tile_size,
             board_size * tile_size,
             board_size * tile_size,
             title),
	  game{board_size},
	  board_size{board_size},
	  tile_s{tile_size},
	  quitBtn{TDT4102::Point{width()-tile_size*4, height()/2-tile_size}, (unsigned)tile_size*2, (unsigned)tile_size/2, "Quit" },
	  resetBtn{TDT4102::Point{width()-tile_size*2, height()/2-tile_size}, (unsigned)tile_size*2, (unsigned)tile_size/2, "Reset"}
{
	
	const TDT4102::Point board_tl{width() / 2 - (board_size * tile_size) / 2,
	                     height() / 2 - (board_size * tile_size) / 2};

	for (int y = 0; y < board_size; ++y) {
		graphical_tiles.emplace_back();
		for (int x = 0; x < board_size; ++x) {
			TDT4102::Point pos{board_tl.x + x * tile_size, board_tl.y + tile_size * y};
			graphical_tiles.back()
				.emplace_back(std::make_unique<Tile>(pos, tile_size, win_value))
				->attach_to(*this);
		}
	}
	add(quitBtn);
	add(resetBtn);
	quitBtn.setVisible(false);
	resetBtn.setVisible(false);
	quitBtn.setCallback(std::bind(&Game_window::cb_quit, this));
	resetBtn.setCallback(std::bind(&Game_window::cb_reset, this));
	update();
}

void Game_window::run() {
    while(!should_close()) {
        handleInput();
    }
}

void Game_window::reset()
{	
	lastStateR = true;
	game.new_game();
	run();
	
}

void Game_window::reset_or_quit(const std::string& text)
{
	hide_tiles();
	quitBtn.setVisible(true);
	resetBtn.setVisible(true);
	draw_text(TDT4102::Point{0, height()/2 - tile_s*2}, text);
 
}

void Game_window::update_tiles()
{
	try {
		for (int y = 0; y < board_size; ++y) {
			for (int x = 0; x < board_size; ++x) {
				update_tile(x, y, game.value(x, y));
			}
		}
	} catch (std::out_of_range& e) {
		std::string error =
			"[Debug] We tried to read outside the playing board:\n" +
			std::string{e.what()};
	}
}
void Game_window::update()
{
	update_tiles();
	check_status();
	next_frame();
}

void Game_window::debug_update() { update_tiles(); }

void Game_window::check_status()
{
	return;
	if (game.win()) {
		reset_or_quit("Congratulations, you won the game!");
	} else if (game.game_over()) {
		reset_or_quit("Game over!");
	}
}

void Game_window::update_tile(int x, int y, int value)
{
	auto&& rect = graphical_tiles[y][x];
	rect->set_value(value);
}

// Capture key presses and pass to action functions
#include "Game_window.h"  // Inkluderer nødvendige header-filer

void Game_window::handleInput() {
    // Oppretter statiske variabler for å holde styr på forrige tastestatus
    static bool lastStateUp = false;
    static bool lastStateRight = false;
    static bool lastStateDown = false;
    static bool lastStateLeft = false;
    static bool lastStateD = false;
    static bool lastStateI = false;
    static bool lastStateH = false;
    static bool lastStateP = false;
    static bool lastStateT = false;
    static bool lastStateF = false;
    static bool lastStateQ = false;

    // Oppdaterer nåværende tastestatus
    bool currentStateUp = is_key_down(KeyboardKey::UP);
    bool currentStateRight = is_key_down(KeyboardKey::RIGHT);
    bool currentStateDown = is_key_down(KeyboardKey::DOWN);
    bool currentStateLeft = is_key_down(KeyboardKey::LEFT);
    bool currentStateR = is_key_down(KeyboardKey::R);
    bool currentStateD = is_key_down(KeyboardKey::D);
    bool currentStateI = is_key_down(KeyboardKey::I);
    bool currentStateH = is_key_down(KeyboardKey::H);
    bool currentStateP = is_key_down(KeyboardKey::P);
    bool currentStateT = is_key_down(KeyboardKey::T);
    bool currentStateF = is_key_down(KeyboardKey::F);
    bool currentStateQ = is_key_down(KeyboardKey::Q);

    // Utfør handlinger for hver tast hvis den nettopp ble trykket ned
    if (currentStateUp && !lastStateUp) {
        game.move(Direction::up);
    }
    if (currentStateRight && !lastStateRight) {
        game.move(Direction::right);	
    }
    if (currentStateDown && !lastStateDown) {
        game.move(Direction::down);
    }
    if (currentStateLeft && !lastStateLeft) {
        game.move(Direction::left);
    }
	update(); //Viktig plassering: MÅ STÅ HER

    if (currentStateR && !lastStateR) {
        reset();
    }
    if (currentStateD && !lastStateD) {
        insert_two_tiles();
    }
    if (currentStateI && !lastStateI) {
        insert_increasing_tiles();
    }
    if (currentStateH && !lastStateH) {
        hide_tiles();
    }
    if (currentStateP && !lastStateP) {
        insert_push_merge_tiles();
    }
    if (currentStateT && !lastStateT) {
        debug_transpose_tiles();
    }
    if (currentStateF && !lastStateF) {
        debug_flip_tiles();
    }
    if (currentStateQ && !lastStateQ) {
        close();
    }

    // Oppdaterer forrige tastestatus
    lastStateUp = currentStateUp;
    lastStateRight = currentStateRight;
    lastStateDown = currentStateDown;
    lastStateLeft = currentStateLeft;
    lastStateR = currentStateR;
    lastStateD = currentStateD;
    lastStateI = currentStateI;
    lastStateH = currentStateH;
    lastStateP = currentStateP;
    lastStateT = currentStateT;
    lastStateF = currentStateF;
    lastStateQ = currentStateQ;

    
}


void Game_window::insert_two_tiles()
{
	game.debug_all_twos();
	debug_update();
};

void Game_window::insert_increasing_tiles()
{
	game.debug_increasing();
	debug_update();
};

void Game_window::insert_push_merge_tiles()
{
	game.debug_push_merge();
	debug_update();
}

void Game_window::debug_transpose_tiles()
{
	game.debug_transpose();
	debug_update();
};
void Game_window::debug_flip_tiles()
{
	game.debug_flip();
	debug_update();
};

void Game_window::hide_tiles() {
	for (auto& v : graphical_tiles) {
		for (auto& t : v) {
			t->hide();
		}
	}
}

void Game_window::cb_quit() {
	close();
}

void Game_window::cb_reset() {
	reset();
}