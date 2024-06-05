#pragma once


#include "Board.h"
#include "Color.h"
#include "ImageAtlas.h"
#include <AnimationWindow.h>
#include "BoardGame.h"
#include "Tasks.h"



struct ChipRenderer {
    static void render(TDT4102::AnimationWindow &window, TDT4102::Point anchor, Player player, int width, int height)
    {
        ImageAtlas atlas = ImageAtlas::getInstance();

        if ( player == Player::NONE ) {
            return;
        }

        auto img = atlas.get_image(player_key(player));

        if ( img )  {
            window.draw_image(anchor, *img, width, height);
        }
        else {
            draw_default_chip(window, anchor, player, width, height);
        }

    }
};

struct BoardRenderer {

    static TDT4102::Color alternate_color(int value, TDT4102::Color first, TDT4102::Color second)
    {

        if ( value % 2 == 0 ) {
            return first;
        } else {
            return second;
        }
    }

    static void draw_checkerboard(TDT4102::AnimationWindow &window, BoardGame &game, TDT4102::Point anchor)
    {

        const int SIZE = game.board.get_size();
        int cell_height = game.get_height() / SIZE;
        int cell_width = game.get_width() / SIZE;

        TDT4102::Point selected = game.selected;

        auto is_selected = [&selected] (int x, int y) {
            return selected.x == x && selected.y == y;
        };


        auto &highlightedTiles = game.get_highlighted();

        for ( int y = 0; y < SIZE; y++ ) {
            for ( int x = 0; x < SIZE; x++ ) {
                int offset_x = x * cell_width;
                int offset_y = y * cell_height;

                TDT4102::Point cell_anchor{anchor.x + offset_x, anchor.y + offset_y};

                TDT4102::Color intended_color = alternate_color(y * (SIZE + 1) + x, TDT4102::Color::gray, TDT4102::Color::khaki);


                if ( ! highlightedTiles.empty() && highlightedTiles[y*SIZE + x] ) {
                    intended_color = TDT4102::Color::ivory;
                }

                if ( is_selected(x, y) ) {
                    intended_color = TDT4102::Color::aqua;
                }

                window.draw_rectangle(
                        cell_anchor,
                        cell_width,
                        cell_height,
                        intended_color);

                Tile &cell = game.board.cell_at(x, y);
                ChipRenderer::render(window, cell_anchor, cell.player, cell_width, cell_height);

            }
        }
    }

    static void render(TDT4102::AnimationWindow &window, BoardGame &checkersBoard, TDT4102::Point anchor) {
        draw_checkerboard(window, checkersBoard, anchor);
    }

};




