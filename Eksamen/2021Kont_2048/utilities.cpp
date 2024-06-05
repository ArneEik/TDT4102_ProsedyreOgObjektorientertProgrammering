#include "utilities.h"

// The following code is provided as part of the exam in TDT4102
// You are not required to read or understand it.

// We use the following code to perform linear interpolation on
// FLTK RGB Colors.

uint8_t lerp(uint8_t begin, uint8_t end, uint8_t n, uint8_t N)
{
	// Linear interpolation
	// Returns a number in the interval [begin, end]
	// with N total steps ([0, N-1])
	// n = 0 => begin
	// n = N => end
	return (end - begin) * n / N + begin;
}

TDT4102::Color lerp_rgb(TDT4102::Color begin, TDT4102::Color end, uint8_t n, uint8_t N)
{
	TDT4102::Color lerped;

	lerped.redChannel = lerp(begin.redChannel, end.redChannel, n, N);
	lerped.greenChannel = lerp(begin.greenChannel, end.greenChannel, n, N);
	lerped.blueChannel = lerp(begin.blueChannel, end.blueChannel, n, N);

	return lerped;
}