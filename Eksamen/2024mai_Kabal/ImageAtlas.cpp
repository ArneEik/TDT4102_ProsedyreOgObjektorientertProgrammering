#include "ImageAtlas.h"
#include "Image.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include "common.h"


// TASK: T7
bool ImageAtlas::has_image(const std::string &key) {
// BEGIN: T7
// Write your answer to assignment T7 here, between the //BEGIN: T7
// and // END: T7 comments. You should remove any code that is
// already there and replace it with your own.
    ImageAtlas &atlas = ImageAtlas::getInstance();
    std::unordered_map<std::string, std::shared_ptr<TDT4102::Image>> &container = atlas.container;

    return container.contains(key);
// END: T7
}

// TASK: T10
void load_image_atlas(const std::filesystem::path &path)
{
// BEGIN: T10
// Write your answer to assignment T10 here, between the //BEGIN: T10
// and // END: T10 comments. You should remove any code that is
// already there and replace it with your own.
    std::ifstream is(path);
    if(!is.is_open()){
        throw std::runtime_error("could not open " + path.string());
    }
    std::string line;
    while(std::getline(is,line)){
        std::istringstream iss(line);
        int rank;
        char suit;
        std::string imagePath;

        if(!(iss>>rank >> suit>> imagePath)){
            throw std::runtime_error("error reading line: " + line);
        }
        std::string key = std::to_string(rank + 1) + suit;
        std::string fullPath = std::string(IMAGE_DIR) + imagePath;
    
        ImageAtlas::getInstance().add_image(key, fullPath);
    }
    is.close();
// END: T10
}

// ========================================
// Do not touch anything below this point
// ========================================

ImageAtlas &ImageAtlas::getInstance() {
    if ( ! ImageAtlas::constructed ) {
        ImageAtlas::instance = ImageAtlas{};
        constructed = true;
    }

    return ImageAtlas::instance;
}

bool ImageAtlas::add_image(const std::string &key, const std::string &filename) {
    ImageAtlas &atlas = getInstance();
    auto &container = atlas.container;

    if ( auto p = get_image(filename) ) {
        return true;
    }

    ImageAtlasStored img = std::make_shared<TDT4102::Image>(filename);

    // If the emplace succeeded, `success` will be true
    auto [_, success] = container.emplace(key, std::move(img));

    return success;
}

ImageAtlasStored ImageAtlas::get_image(const std::string &key) {

    ImageAtlas &atlas = getInstance();
    auto &container = atlas.container;

    if ( has_image(key) ) {
        return container.at(key);
    }

    return {};
}

std::string extension_to_lower(const std::string &from)
{

    std::string result{};
    result.reserve(from.size());

    for ( char c : from ) {
        result += std::tolower(c);
    }

    return result;
}

bool ImageAtlas::constructed = false;
ImageAtlas ImageAtlas::instance{};



void ImageAtlas::load_default_atlas() {
   auto &atlas = ImageAtlas::getInstance();

   atlas.add_image("1C", "./images/1C.png");
   atlas.add_image("2C", "./images/2C.png");
   atlas.add_image("3C", "./images/3C.png");
   atlas.add_image("4C", "./images/4C.png");
   atlas.add_image("5C", "./images/5C.png");
   atlas.add_image("6C", "./images/6C.png");
   atlas.add_image("7C", "./images/7C.png");
   atlas.add_image("8C", "./images/8C.png");
   atlas.add_image("9C", "./images/9C.png");
   atlas.add_image("10C", "./images/10C.png");
   atlas.add_image("11C", "./images/11C.png");
   atlas.add_image("12C", "./images/12C.png");
   atlas.add_image("13C", "./images/13C.png");

   atlas.add_image("1H", "./images/1H.png");
   atlas.add_image("2H", "./images/2H.png");
   atlas.add_image("3H", "./images/3H.png");
   atlas.add_image("4H", "./images/4H.png");
   atlas.add_image("5H", "./images/5H.png");
   atlas.add_image("6H", "./images/6H.png");
   atlas.add_image("7H", "./images/7H.png");
   atlas.add_image("8H", "./images/8H.png");
   atlas.add_image("9H", "./images/9H.png");
   atlas.add_image("10H", "./images/10H.png");
   atlas.add_image("11H", "./images/11H.png");
   atlas.add_image("12H", "./images/12H.png");
   atlas.add_image("13H", "./images/13H.png");

   atlas.add_image("1S", "./images/1S.png");
   atlas.add_image("2S", "./images/2S.png");
   atlas.add_image("3S", "./images/3S.png");
   atlas.add_image("4S", "./images/4S.png");
   atlas.add_image("5S", "./images/5S.png");
   atlas.add_image("6S", "./images/6S.png");
   atlas.add_image("7S", "./images/7S.png");
   atlas.add_image("8S", "./images/8S.png");
   atlas.add_image("9S", "./images/9S.png");
   atlas.add_image("10S", "./images/10S.png");
   atlas.add_image("11S", "./images/11S.png");
   atlas.add_image("12S", "./images/12S.png");
   atlas.add_image("13S", "./images/13S.png");

   atlas.add_image("1D", "./images/1D.png");
   atlas.add_image("2D", "./images/2D.png");
   atlas.add_image("3D", "./images/3D.png");
   atlas.add_image("4D", "./images/4D.png");
   atlas.add_image("5D", "./images/5D.png");
   atlas.add_image("6D", "./images/6D.png");
   atlas.add_image("7D", "./images/7D.png");
   atlas.add_image("8D", "./images/8D.png");
   atlas.add_image("9D", "./images/9D.png");
   atlas.add_image("10D", "./images/10D.png");
   atlas.add_image("11D", "./images/11D.png");
   atlas.add_image("12D", "./images/12D.png");
   atlas.add_image("13D", "./images/13D.png");

   atlas.add_image("back", "./images/backR.png");
}
