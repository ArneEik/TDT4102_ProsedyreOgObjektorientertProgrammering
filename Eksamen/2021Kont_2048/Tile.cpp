#include "Tile.h"
#include "utilities.h"


Tile::Tile(TDT4102::Point pos, int size, int max_value)
	: rect{pos, (unsigned)size, (unsigned)size, ""},
	//   label{{0, pos.y + size / 2 + fl_height() / 4}, ""},
	  size{size},
	  max_value{max_value}
{
	init();
}

void Tile::init()
{
	rect.setButtonColor(TDT4102::Color::black);
	set_value(0);
}

void Tile::set_value(int value)
{
	if (value == 0) {
		// An empty tile
		rect.setButtonColor(TDT4102::Color::gray);
		rect.setLabelColor(TDT4102::Color::black);
		rect.setLabel("");
	} else {
		// Using FLTK RGB colors to make darker and darker shades,
		// instead of the indexed virtual colormap [0, 255]
		int current_step = std::log2(value) - 1;
		int max_step = std::log2(max_value) - 1;

		TDT4102::Color darker = lerp_rgb(TDT4102::Color{YELLOW}, TDT4102::Color{DARK_ORANGE}, current_step, max_step);

		rect.setButtonColor(darker);
		// label.set_label(std::to_string(value));
		rect.setLabel(std::to_string(value));
	}

	// center_label();
}

// void Tile::center_label()
// {
// 	// We're adjusting only on x axis
// 	// We can't manipulate positions with absolute values,
// 	// so we calculate the difference we need to move().

// 	// Existing difference between rect.x and label.x
// 	TDT4102::Point rect_pos = rect.;
// 	TDT4102::Point label_pos = label.point(0);

// 	// Calculate difference between old and new position
// 	int label_width = fl_width(label.label().c_str());
// 	int rect_center_x = rect_pos.x + (size / 2);
// 	int diff_x = std::abs(label_pos.x - rect_center_x) - 0.5 * label_width;

// 	// move relatively to current text position
// 	label.move(diff_x, 0);
// }

void Tile::attach_to(TDT4102::AnimationWindow& win)
{
	win.add(rect);
	// win.attach(label);
}

void Tile::hide() {
	rect.setVisible(false);
}