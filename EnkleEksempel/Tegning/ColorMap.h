#include "subprojects\animationwindow\src\Color.cpp"
#include "std_lib_facilities.h"
#include "map"

map<string, TDT4102::Color> stringToColor{
    {"white", TDT4102::Color::white},
    {"black", TDT4102::Color::black},
    {"red", TDT4102::Color::red},
    {"blue", TDT4102::Color::blue},
    {"green", TDT4102::Color::green}
};
map<int, TDT4102::Color> colorMap = {
        {0, TDT4102::Color::white}, // Eraser color
        {1, TDT4102::Color::black},
        {2, TDT4102::Color::red},
        {3, TDT4102::Color::blue},
        {4, TDT4102::Color::green}
    };