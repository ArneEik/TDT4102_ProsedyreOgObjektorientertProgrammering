#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "bouncingBall.h"

constexpr Point BOUNCE_WINDOW_TOP_LEFT{50, 50};
constexpr int BOUNCE_WINDOW_WIDTH{800}; 
constexpr int BOUNCE_WINDOW_HEIGHT{500};

map<int, Color> ball_colour{{1, Color::light_coral},
                            {2, Color::light_green},
                            {3, Color::aquamarine},
                            {4, Color::purple}
};

istream& operator>>(istream& is, Config& cfg){
    is >> cfg.colour_up >> cfg.colour_down >> cfg.velocity;
    return is;
}

void bouncingBall(){
    AnimationWindow window{BOUNCE_WINDOW_TOP_LEFT.x, BOUNCE_WINDOW_TOP_LEFT.y, 
                           BOUNCE_WINDOW_WIDTH, BOUNCE_WINDOW_HEIGHT, "Bouncing ball"};
    
    const int radius{30};
    int alpha{1};
    int velocity{2};
    Color colour_up{Color::blue};
    Color colour_down{Color::blue};
    int x{0};
    int y{360};
    int increment_x{0};
    int increment_y{0};
    int count_bounce_top{0};
    int count_bounce_bottom{0};
    int count_num_passes{0};

    Config slow = {1, 1, 0};
    Config fast = {1, 1, 0};

    // read in the configurations
    filesystem::path file_name{"konfigurasjon.txt"};
    ifstream is{file_name};
    is >> slow >> fast; 

    // initialise the run
    velocity = slow.velocity;
    colour_up = ball_colour.at(slow.colour_up);
    colour_down = ball_colour.at(slow.colour_down);

    while (!window.should_close()) {
        // determine increments based on the velocity
        increment_x = velocity * cos(alpha);
        increment_y = velocity * sin(alpha);

        // movement i x-direction
        if ((increment_x + x) > window.width()) {
            // reached right side - wrap around to the leftmost
            x = 0;
            // increment counter which counts number of full left-to-right passes
            count_num_passes++;
            // alternate between slow and fast configuration every fifth pass
            if (count_num_passes % 5 == 0) {
                if (velocity == slow.velocity) {
                    velocity = fast.velocity;
                    colour_up = ball_colour.at(fast.colour_up);
                    colour_down = ball_colour.at(fast.colour_down);
                } else {
                    velocity = slow.velocity;
                    colour_up = ball_colour.at(slow.colour_up);
                    colour_down = ball_colour.at(slow.colour_down);
                }
            }
        } else {
            // moving rightwards
            x += increment_x;
        }

        // movement i y-direction
        if (((count_bounce_top + count_bounce_bottom) % 2) == 0) {
            // move upwards
            // check for hitting top
            if ((y - increment_y) < radius) {
                y = radius;
                count_bounce_top++;
            } else {
                y -= increment_y;
            }
            window.draw_circle({x, y}, radius, colour_up); 
        } else {
            // move downwards
            // check for hitting bottom
            if ((increment_y + y) > window.height() - radius) { 
                y = window.height() - radius;
                count_bounce_bottom++;
            } else {
                y += increment_y;
            }
            window.draw_circle({x, y}, radius, colour_down);
        }
    
        window.next_frame();
    }
}

