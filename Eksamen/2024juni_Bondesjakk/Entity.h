#pragma once

#include "AnimationWindow.h"

struct Entity {


    ~Entity() {}

    explicit Entity(TDT4102::Point position_, int width_, int height_)
        : position{position_}, width{width_}, height{height_}
    {}


    Entity() = default;
    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;
    Entity(Entity&& other) = default;
    Entity& operator=(Entity&& other) = default;


    TDT4102::Point get_position() const {
        return position;
    }

    void set_position(TDT4102::Point new_pos) {
        position = new_pos;
    }

    void set_width(int width_) {
        width = width_;
    }

    void set_height(int height_) {
        height = height_;
    }

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }

    virtual void update() {
        // No-op as base entity
    }


private:
    TDT4102::Point position;
    int width;
    int height;

};





