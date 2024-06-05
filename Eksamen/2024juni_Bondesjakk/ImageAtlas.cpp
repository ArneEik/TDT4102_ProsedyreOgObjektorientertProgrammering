#include <iterator>
#include <algorithm>

#include "ImageAtlas.h"
#include "Image.h"


// TASK: T5
std::shared_ptr<TDT4102::Image> ImageAtlas::get_image(const std::string &key)
{
    ImageAtlas &atlas = getInstance();

    std::unordered_map<std::string, std::shared_ptr<TDT4102::Image>> &container = atlas.container;

// BEGIN: T5
// Write your answer to assignment T5 here, between the //BEGIN: T5
// and // END: T5 comments. You should remove any code that is
// already there and replace it with your own.
    if(container.count(key) != 0){
        return container.at(key);
    }
    return {};
// END: T5
}

// ============================================================
// ============================================================
// Do not touch anything below this point
// ============================================================
// ============================================================


bool ImageAtlas::constructed = false;
ImageAtlas ImageAtlas::instance{};


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

    if ( auto p = get_image(key) ) {
        return true;
    }

    std::shared_ptr<TDT4102::Image> img = std::make_shared<TDT4102::Image>(filename);

    auto [_, success] = container.emplace(key, std::move(img));

    return success;
}

std::string extension_to_lower(const std::string &from)
{

    std::string result{};

    auto inserter = std::back_inserter(result);

    std::transform(std::begin(from), std::end(from), inserter, [] (auto c) {
            return std::tolower(c);
    });

    return result;
}
