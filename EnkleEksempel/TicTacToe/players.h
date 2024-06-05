#pragma once
#include <string>

class PlayerInfo {
public:
    PlayerInfo(const std::string& name, const std::string& color);
    std::string getName() const;
    std::string getColor() const;

private:
    std::string name;
    std::string color;
};
