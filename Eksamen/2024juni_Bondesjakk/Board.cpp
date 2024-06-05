#include <cstdlib>
#include <fstream>

#include "Board.h"



// TASK: T1
int Board::get_size() const {
// BEGIN: T1
// Write your answer to assignment T1 here, between the //BEGIN: T1
// and // END: T1 comments. You should remove any code that is
// already there and replace it with your own.
    return size;
// END: T1
}


// TASK: T11
Board load_board(const std::filesystem::path &path) {

// BEGIN: T11
// Write your answer to assignment T11 here, between the //BEGIN: T11
// and // END: T11 comments. You should remove any code that is
// already there and replace it with your own.
    std::ifstream is(path);
    if(!is.is_open()){
        throw std::runtime_error("could not open " + path.string());
    }
    int sizeN;
    is>>sizeN;

    Board newBoard = Board::create_blank(sizeN);
    
    for(int y=0; y<sizeN; y++){
        for(int x = 0; x<sizeN; x++){
            int state;
            is>>state;
            switch (state)
            {
            case 1:
                newBoard.cell_at(x,y).player = Player::ONE;
                break;
            case 2:
                newBoard.cell_at(x,y).player = Player::TWO;
                break;
            
            default:
                newBoard.cell_at(x,y).player = Player::NONE;
                break;
            }   
        }
    }
  return newBoard;
// END: T11
}

// ============================================================
// ============================================================
// Do not touch anything below this point
// ============================================================
// ============================================================

Board::Board(int size_)
    : size{size_} {
        cells.resize(size*size);
    }

// Delegating constructor
Board::Board() : Board{8} {}

Board Board::create_blank(int size_) {

    auto result = Board{size_};

    int SIZE = result.get_size();
    result.cells.resize(SIZE * SIZE, Tile{Player::NONE, false});


    // Populate board
    for ( int x = 0; x < SIZE; x++ ) {
        result.cell_at(x,1).player = Player::ONE;
        result.cell_at(x,1).firstMove = true;
    }


    for ( int x = 0; x < SIZE; x++ ) {
        result.cell_at(x,SIZE-2).player = Player::TWO;
        result.cell_at(x,SIZE-2).firstMove = true;
    }

    return result;

}



void Board::move(TDT4102::Point from, TDT4102::Point to)
{
    Player player = cell_at(from.x, from.y).player;
    cell_at(from.x, from.y).player = Player::NONE;
    cell_at(to.x, to.y).player = player;
}

Tile &Board::cell_at(int x, int y) {
    return cells.at(y * size + x);
}


const Tile &Board::cell_at(int x, int y) const {
    return cells.at(y * size + x);
}

std::vector<Tile> const &Board::get_cells() const {
    return cells;
}
