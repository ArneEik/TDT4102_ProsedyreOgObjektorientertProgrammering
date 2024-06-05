#include "Game.h"

Game::Game(int board_size, int win_value)
	: board_size(board_size),
	  board(board_size * board_size),
	  win_value{win_value}
{
	new_game();
}

// TASK
int Game::index(int x, int y) const
{
	// BEGIN: G1
	

	return x*board_size + y;
	// END: G1
}

// TASK
int Game::at(int x, int y) const {
    // BEGIN: G2
    return board.at(index(x, y));
    // END: G2
}

int& Game::at(int x, int y) {
    // BEGIN: G3
    if ((x < 0) || (static_cast<int>(board_size) <= x) || (y < 0) || (static_cast<int>(board_size) <= y)) {
        throw std::out_of_range("Index is out of range, (x, y) = (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
    return board.at(index(x, y));
    // END: G3
}


// TASK
void Game::new_game()
{
	// BEGIN: G4
	for(int i=0; i<board_size * board_size; ++i){
		board[i] = 0;
	}
	place_new_2();
	place_new_2();


	
	// END: G4
}

// TASK
// Prerequisites: board does have a free 0-spot
void Game::place_new_2()
{
	// BEGIN: G5
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0,static_cast<int>(board_size)*static_cast<int>(board_size)-1);	
	int randNum1 = dis(gen);
	int randnum2 = dis(gen);

	while(board.at(randNum1) != 0) {	
		randNum1 = dis(gen);	

		}
	board.at(randNum1) = randNum1 - randnum2 > 0 ? 2 : 4;

	// END: G5
}

// TASK
void Game::flip() 
{
    // BEGIN: G6
    for (int i = 0; i < board_size / 2; ++i) {
        for (int j = 0; j < board_size; ++j) {
            std::swap(board[index(i, j)], board[index(board_size - i - 1, j)]);
        }
    }
    // END: G6
}
// TASK
void Game::transpose()
{
	// BEGIN: G7
	std::vector<int> scratchBoard(board_size * board_size);
	scratchBoard = board;
	for(int i = 0; i < board_size; i++){
		for(int j = 0; j< board_size; j++){
		board.at(index(i,j)) = scratchBoard.at(index(j,i));
		}
	}	
	// END: G7
}

// TASK
void Game::push_right()
{
	// BEGIN: G8
	// std::cout<<"eg er kalla høgre no ";

	std::vector<int> scratchBoard(board_size * board_size);
	scratchBoard = board;
	for(int y = 0; y < board_size; ++y){
		std::vector<int> newRow(board_size,0);
		int pos = board_size -1;
		for(int x = board_size-1;  x >= 0;  x--){
			int value = board.at(index(x,y));
			if(value != 0){
				newRow.at(pos) = value;
				pos--;
			}
		}
		for(int x = 0; x< board_size; x++){
			board.at(index(x,y))  = newRow.at(x);
		}
	}
	// END: G8
}

// TASK
void Game::merge_right() {
    // BEGIN: G9
    // std::cout << "Merge right called\n";

    bool merged;
    do {
        merged = false;
        push_right();
		// std::cout << "Merge right called\n";
		
        for (int y = 0; y < board_size; y++) {
            for (int x = board_size - 1; x > 0; --x) {
                int currentIndex = index(x, y);
                int previousIndex = index(x - 1, y);
                if (board.at(currentIndex) == board.at(previousIndex) && board.at(currentIndex) != 0) {
                    board.at(currentIndex) += board.at(previousIndex);
                    board.at(previousIndex) = 0;
                    merged = true;
                }
            }
        }

        if (merged) {
            push_right(); // Flytt brikkene til høyre igjen etter sammenslåing

        }

    } while (merged);

    // END: G9
}

// TASK
void Game::move_right()
{
	// BEGIN: G10
	merge_right();
	// END: G10
}

// TASK
void Game::move_down()
{
	// BEGIN: G11
	transpose();
	merge_right();
	transpose();
	
	// END: G11
}

// TASK
void Game::move_left()
{
	// BEGIN: G12
	flip();
	merge_right();
	flip();
	// END: G12
}

// TASK
void Game::move_up()
{
	// BEGIN: G13
	transpose();
	move_left();
	transpose();
	
	// END: G13
}

// TASK
bool Game::free_spots() const
{
	// BEGIN: G14
	for(int i=0; i<board_size*board_size;i++){
		if(board.at(i) == 0)return true;
	}
	return false;
	// END: G14
}

// TASK
void Game::tick()
{
	// BEGIN: G15
	if(free_spots()){
		place_new_2();
	}
	
	// END: G15
}

// TASK
bool Game::win() const
{
	// BEGIN: G16
	int score = 0; //ville heller hat score som ein medlemsvariabel og oppdatert den kvar gong det vart lagt til eit nytt element
	for(int i=0; i<board_size*board_size;i++){
		score += board.at(i);
	}
	
	return win_value <= score;
	// END: G16
}

// TASK
// Prerequisites: all tiles are non-zero
bool Game::legal_moves() const {
    // BEGIN: G17
    for (int y = 0; y < board_size; ++y) {
        for (int x = 0; x < board_size; ++x) {
            int currentIndex = index(x, y);
            int currentValue = board.at(currentIndex);

            // Sjekk høyre og ned (for å unngå dobbeltsjekking)
            if (x < board_size - 1) {
                int rightIndex = index(x + 1, y);
                if (currentValue == board.at(rightIndex)) {
                    return true;
                }
            }
            if (y < board_size - 1) {
                int downIndex = index(x, y + 1);
                if (currentValue == board.at(downIndex)) {
                    return true;
                }
            }
        }
    }
    return free_spots();
    // END: G17
}




/**** Provided code ****/

// API version of tile value - const external interface
int Game::value(int x, int y) const { return at(x, y); }

// This function keeps track of changes to the board
// and calls the move function requested by the player
void Game::move(Direction direction)
{
	// We have not moved any tiles yet
	moved = false;

	// Keep the old board matrix for comparison
	std::vector<int> old_board{board};

	if (status() == Status::playing) {
		switch (direction) {
		case Direction::up:
			move_up();
			break;
		case Direction::right:
			move_right();
			break;
		case Direction::down:
			move_down();
			break;
		case Direction::left:
			move_left();
			break;
		}
	}

	// Did we move anything?
	if (board != old_board) {
		moved = true;
	}

	tick();
}

// We use this to figure out if a game
// is won, game over or if the player still
// can play legal moves
Game::Status Game::status() const
{
	if (win()) {
		std::cout<<"win";
		return Status::win;
	}

	if (free_spots() || legal_moves()) {
		return Status::playing;
	}
	std::cout<<"tap";
	return Status::game_over;
	
}

bool Game::game_over() const { return status() == Status::game_over; }

std::ostream& operator<<(std::ostream& os, const Game& g)
{
	for (int i = 0; i < g.board_size; ++i) {
		for (int j = 0; j < g.board_size; ++j) {
			std::cout << g.at(j, i) << " ";
		}
		std::cout << '\n';
	}

	return os;
}

// Debug methods - debug API
void Game::debug_all_twos()
{
	static const std::array<int, 16> debug_board_all_twos{
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

	std::copy(debug_board_all_twos.begin(),
	          debug_board_all_twos.end(),
	          board.begin());
	tick();
}

void Game::debug_increasing()
{
	static const std::array<int, 16> debug_board_increasing{
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	std::copy(debug_board_increasing.begin(),
	          debug_board_increasing.end(),
	          board.begin());
	tick();
}

void Game::debug_push_merge()
{
	// clang-format off
	static const std::array<int, 16> debug_board_push_merge{
		2,0,2,0,
		0,2,2,4,
		0,2,2,2,
		8,8,8,8
	};
	// clang-format on

	std::copy(debug_board_push_merge.begin(),
	          debug_board_push_merge.end(),
	          board.begin());
	tick();
}

void Game::debug_flip() { flip(); }
void Game::debug_transpose() { transpose(); }
