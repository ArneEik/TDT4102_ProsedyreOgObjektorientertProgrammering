#include "players.h"

// Konstruktør
PlayerInfo::PlayerInfo(const std::string& name, const std::string& color)
    : name(name), color(color) {}

// Returnerer spillernavn
std::string PlayerInfo::getName() const {
    return name;
}

// Returnerer spillerfarge
std::string PlayerInfo::getColor() const {
    return color;
}
