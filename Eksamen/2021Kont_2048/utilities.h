#pragma once
#include <stdint.h>
#include "Color.h"

// The following code is provided as part of the exam in TDT4102
// You are not required to read or understand it.

union RGBA {
	// Be aware of endianness
	// This is OK for tdt4102 2021 and the assumptions we make
	uint32_t rgba = 0;
	struct {
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t r;
	} c;
};

uint8_t lerp(uint8_t begin, uint8_t end, uint8_t n, uint8_t N);

TDT4102::Color lerp_rgb(TDT4102::Color begin, TDT4102::Color end, uint8_t n, uint8_t N);
