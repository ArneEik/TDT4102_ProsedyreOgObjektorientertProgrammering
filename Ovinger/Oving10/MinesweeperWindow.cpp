#include "MinesweeperWindow.h"
#include <iostream>
#include <random>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 3) * cellSize, title},
	width{width}, height{height}, mines{mines}, minesLeftUser{mines},
	gameFeedback{{0, (height) * cellSize}, static_cast<unsigned int>(width * cellSize), static_cast<unsigned int>(cellSize), ""},
	gameRestart{{0, (height+1) * cellSize}, 4 * cellSize, cellSize, "Restart"},
	gameQuit{{(width - 4) * cellSize, (height+1) * cellSize}, 4 * cellSize, cellSize, "Quit"}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp); 
		}
	}
	// Legg til miner paa tilfeldige posisjoner
	int i = 0;
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distrubution(0,tiles.size());
	while(i<mines){
		int spot = distrubution(generator);
		if (!tiles[spot]->getIsMine()){
			tiles[spot]->set_is_mine();
			i++;
		}
	}
	//Det starter med aa vise hvor mange miner som er igjen
	gameFeedback.setText("Mines left: " + to_string(minesLeftUser));
	add(gameFeedback);

	// Legger til buttons for å avslutte og restarte spillet
	gameRestart.setCallback(std::bind(&MinesweeperWindow::cb_restart, this));
	gameRestart.setLabelColor(Color::black);
	add(gameRestart);
	gameQuit.setCallback(std::bind(&MinesweeperWindow::cb_quit, this));
	gameQuit.setLabelColor(Color::black);
	add(gameQuit);
	gameRestart.setVisible(false);
	gameQuit.setVisible(false);

}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	shared_ptr<Tile>& tile = at(xy);
		// Reagerer kun hvis Tile er lukket
	if (tile->getState() != Cell::closed) {
		return;
	}
	tile->open();
	// Hvis Tilen er en mine er spillet over
	if (tile->getIsMine()) {
		gameOver();
		return;
	}

	
	//remainingTiles--;
	vector<Point> adjPoints = adjacentPoints(xy);
	int minesAround = countMines(adjPoints);
	if (minesAround > 0) { 
		// Hvis det er miner i naerheten setter vi labelen
		tile->setAdjMines(minesAround);
	}
	else {
		// Hvis det ikke er noen miner i naerheten vil vi aapne tilene rundt rekursivt 
		for (Point p : adjPoints) {
			openTile(p);
		}
	}
	int tileLeftCount = 0;
	for(auto tile:tiles){
		if (tile->getState() == Cell::closed) {
			++tileLeftCount;
		}
	}
	if(tileLeftCount == mines){
		gameIsWon();
	}
	
}
	
void MinesweeperWindow::flagTile(Point xy) {
	shared_ptr<Tile>& tile = at(xy);
	if(tile->getState() != Cell::open){
		tile->flag();
		if(tile->getState() == Cell::flagged){
		--minesLeftUser;
		}else if(minesLeftUser<mines){
			++minesLeftUser;
		}
	}
	gameFeedback.setText("Mines left: " + to_string(minesLeftUser));
}
	
int MinesweeperWindow::countMines(vector<Point> points){
	int count = 0;
	for(auto point:points){
		if (at(point)->getIsMine()){
			++count;
		}
	}
	return count;
}

void MinesweeperWindow::gameOver()
{
	for(auto tile:tiles){
		if (tile->getIsMine()) {
			tile->setState(Cell::closed);
			tile->open();
		}
	}
	gameIsLost();

}

void MinesweeperWindow::gameIsLost()
{
	addGameEndMenu("Looooooooossseeeeerrrr");
}
void MinesweeperWindow::gameIsWon()
{
	addGameEndMenu("you won");
}
//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	
	Point xy{this->get_mouse_coordinates()};

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
}

void MinesweeperWindow::cb_restart() {

	for (auto tile : tiles) {
		tile->reset();
	}

	// Fjerner spillsluttmenyen
	gameRestart.setVisible(false);
	gameQuit.setVisible(false);

	// Plasser nye miner
	int mineCount = 0;
	while (mineCount < mines) {
		int pos = rand() % tiles.size();
		if (!tiles[pos]->getIsMine()) {
			tiles[pos]->set_is_mine();
			++mineCount;
		}
	}

	// Nullstiller variabler
	minesLeftUser = mines;
	gameFeedback.setText(("Mines left: " + to_string(minesLeftUser)));
}

void MinesweeperWindow::cb_quit(){
	close();
}
void MinesweeperWindow::addGameEndMenu(string s) {
	// Gir feedback om at spillets resultat
	gameFeedback.setText(s);

	//Legg til quit og restart knapp
	gameRestart.setVisible(true);
	gameQuit.setVisible(true);
}