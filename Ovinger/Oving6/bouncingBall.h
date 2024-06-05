#pragma once

void bouncingBall();

struct Config{ 
    int colour_up;
    int colour_down;
    int velocity;
};

istream& operator>>(istream& is, Config& cfg);