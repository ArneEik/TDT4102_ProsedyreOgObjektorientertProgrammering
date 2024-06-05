#include "XrowWindow.h"

XrowWindow::XrowWindow(int width, int height, const char* title)
    : AnimationWindow{30, 30, width, height, title}, game(6, 7),
      player1("Player 1", "Red"), player2("Player 2", "Yellow"),
      statusBox(Point{10, 60}, width - 20, 30, "Player 1's turn") {
    
    initializeBoard();
    updateStatus();
}

void XrowWindow::initializeBoard() {
    int buttonSize = 50;
    int margin = 10;

    // Opprett kolonne-knapper for å slippe brikker
    for (int col = 0; col < 7; ++col) {
        buttons.push_back(std::make_unique<TDT4102::Button>(
            Point{margin + col * buttonSize, 0}, buttonSize, buttonSize, std::to_string(col)
        ));
        buttons.back()->setCallback([this, col]() { dropPiece(col); });
        add(*buttons.back());
    }

    // Legg til statusboks for å vise hvilken spiller sin tur det er
    add(statusBox);
}

void XrowWindow::updateBoard() {
    int buttonSize = 50;
    int margin = 10;
    const auto& board = game.getBoard();

    // Tegn spillebrettet basert på spillets tilstand
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            TDT4102::Color color = playerToColor.at(board[row][col]);
            draw_rectangle(Point{margin + col * buttonSize, margin + (row + 1) * buttonSize}, buttonSize, buttonSize, color);
        }
    }
}

void XrowWindow::dropPiece(int column) {
    if (game.dropPiece(column)) {
        updateBoard();
        updateStatus();
    }
}

void XrowWindow::updateStatus() {
    if (game.checkWin()) {
        std::string winnerText = (game.getWinner() == PlayerType::PLAYER_1) ? "Player 1 wins!" : "Player 2 wins!";
        statusBox.setText(winnerText);
    } else {
        std::string currentPlayerText = (game.currentPlayer() == PlayerType::PLAYER_1) ? "Player 1's turn" : "Player 2's turn";
        statusBox.setText(currentPlayerText);
    }
}

void XrowWindow::run() {
    while (!should_close()) {
        // Tegn spillebrettet
        draw_rectangle({0, 0}, width(), height(), TDT4102::Color::white);
        updateBoard();

        // Oppdater status
        updateStatus();

        // Vent til neste frame
        next_frame();
    }
}
