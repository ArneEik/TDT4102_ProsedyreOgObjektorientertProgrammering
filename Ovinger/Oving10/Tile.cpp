#include "Tile.h"



// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open()
{
	if(!((state == Cell::open) || (state == Cell::flagged))){
		state = Cell::open;
		this->setButtonColor(TDT4102::Color::white);
		if(isMine){
			this->set_label("X");
			this->set_label_color(TDT4102::Color::red);
		}
	}
}

void Tile::flag()
{
	switch (state) { // Sjekk om ruten er flagget fra for, enten flag eller unflag
	case Cell::closed:
		set_label(cellToSymbol.at(Cell::flagged));
		state = Cell::flagged;
		set_label_color(TDT4102::Color::black);
		break;
	case Cell::flagged:
		set_label(cellToSymbol.at(Cell::closed));
		state = Cell::closed;
		break;
	case Cell::open:; // Kan ikke flagge åpen rute, gjør ingenting
	}
}

void Tile::setAdjMines(int n){
	set_label(std::to_string(n));
	set_label_color(minesToColor.at(n));
}
void Tile::reset()
{
	state = Cell::closed;
	setButtonColor(TDT4102::Color::silver);
	set_label(cellToSymbol.at(Cell::closed));
	isMine = false;
}