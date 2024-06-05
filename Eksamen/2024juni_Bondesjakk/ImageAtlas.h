#pragma once

#include "AnimationWindow.h"


class ImageAtlas {

public:
  static ImageAtlas &getInstance();

  static bool add_image(const std::string &key, const std::string &filename);
  static std::shared_ptr<TDT4102::Image> get_image(const std::string &filename);

private:
    ImageAtlas() = default;

    std::unordered_map<std::string, std::shared_ptr<TDT4102::Image>> container{};

    void makeInstance();

    static ImageAtlas instance;
    static bool constructed;

};




