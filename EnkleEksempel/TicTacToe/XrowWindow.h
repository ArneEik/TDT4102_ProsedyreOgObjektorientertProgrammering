#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "widgets/TextInput.h"
#include "widgets/Button.h"
#include "Game.h"
#include "players.h"
#include <vector>
#include <memory>

class XrowWindow : public AnimationWindow {
public:
    XrowWindow(int width, int height, const char* title);

    void run(); // Deklarasjon av run-funksjonen

private:
    Game game;
    std::vector<std::unique_ptr<TDT4102::Button>> buttons; // Bruker unique_ptr for knapper
    TDT4102::TextInput statusBox; // Direkte instans av TextInput
    PlayerInfo player1;
    PlayerInfo player2;
    std::map<PlayerType, TDT4102::Color> playerToColor{
        {PlayerType::PLAYER_1, TDT4102::Color::blue},
        {PlayerType::PLAYER_2, TDT4102::Color::red},
        {PlayerType::NONE, TDT4102::Color::white}
    };

    void initializeBoard();
    void updateBoard();
    void dropPiece(int column);
    void updateStatus();
};
