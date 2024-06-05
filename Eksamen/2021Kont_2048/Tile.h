#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include <string>
#include <cmath>

struct Tile {
	static inline constexpr unsigned int YELLOW = 0xFEF00100;
	static inline constexpr unsigned int DARK_ORANGE = 0xF0050500;

	Tile(TDT4102::Point pos, int size, int max_value);
	void init();
	void set_value(int value);
	// void center_label();
	void attach_to(TDT4102::AnimationWindow& win);
	void hide();

  private:
	TDT4102::Button rect;
	int size;
	int max_value;
};
