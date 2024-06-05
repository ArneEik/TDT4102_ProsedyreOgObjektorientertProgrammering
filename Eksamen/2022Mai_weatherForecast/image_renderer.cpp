#include "image_renderer.h"
#include "AnimationWindow.h"
#include "util.h"
#include <filesystem>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <algorithm>


// Task R1: Color lookup
//
// Write a function that returns the Graph_lib
// color type corresponding to the color name given in the parameter
// color. To do this, you may use the map color_map defined in
// image_renderer.h. If the parameter color refers to an invalid
// color the function should throw an exception.
TDT4102::Color ImageRenderer::get_color_value(string color)
{
  // BEGIN: R1
  //
  // Write your answer to assignment R1 here, between the // BEGIN: R1
  // and // END: R1 comments. You should remove any code that is
  // already there and replace it with your own.
  if (color_map.find(color) == color_map.end()) {
    throw std::out_of_range("Color not found in the color map");
  }
  return color_map[color];

  // END: R1
}

// Task R2: Add color references
//
// Write a function that given a color reference (parameter ref)
// and a color name (parameter color_name) adds an entry to the
// colors vector. Use the function get_color_value to look up the
// color names.
void ImageRenderer::add_color(char ref, string color_name)
{
  // BEGIN: R2
  //
  // Write your answer to assignment R2 here, between the // BEGIN: R2
  // and // END: R2 comments. You should remove any code that is
  // already there and replace it with your own.
  colors[ref] = get_color_value(color_name);

  // END: R2
}

// Task R3: Add image rows
//
// Write a function that adds a new vector to the image
// vector. The intention is that this function is called for every additional
// row of pixels found when reading the image file.  Remember that
// the new vector must be instantiated as a
// unique_pointer.
void ImageRenderer::add_line()
{
  // BEGIN: R3
  //
  // Write your answer to assignment R3 here, between the // BEGIN: R3
  // and // END: R3 comments. You should remove any code that is
  // already there and replace it with your own.
  image.push_back(std::make_unique<std::vector<TDT4102::Color>>());

  // END: R3
}

// Task R4: Add image pixels
//
// Write a function that adds a pixel to the image. Since the image
// data is read line-by-line, always add the pixel to the most
// recently added vector in the image vector.
void ImageRenderer::add_pixel(TDT4102::Color color)
{
  if (image.size() == 0) {
    throw runtime_error(
        "Remember to insert a call to the add_line funtion for every image "
        "line you read in the read_image_pixels function");
  }

  // BEGIN: R4
  //
  // Write your answer to assignment R4 here, between the // BEGIN: R4
  // and // END: R4 comments. You should remove any code that is
  // already there and replace it with your own.
  if (image.empty()) {
    throw runtime_error("Call add_line() before adding pixels.");
  }
  image.back()->push_back(color);

  // END: R4
}

// Task R5: Reading the header
//
// Complete the function for reading the image header. Most of the
// hard work is already done for you but the part for reading the
// actual values into the variables width, height, and ncolors
// is missing. Your task is to add this.
// std::string full_path ="C:/Users/eikel/Documents/AIS/2semester/TDT4102/EksamenOppgaver/2022Mai/symbols/rain.sxpm";

void ImageRenderer::read_image(string file_name)
{
    // Use filesystem to create the full path
    std::filesystem::path base_path = std::filesystem::current_path();
    std::filesystem::path full_path = base_path / "symbols" / (file_name);

    std::cout << "Trying to open file: " << full_path << std::endl;

    std::ifstream image_file_stream(full_path);
    if (!image_file_stream.is_open()) {
        std::cerr << "Failed to open file: " << full_path << std::endl;
    }

    std::string header;
    if (std::getline(image_file_stream, header)) {
        std::cout << "Header line: " << header << std::endl;
    } else {
        std::cerr << "Failed to read header line from file: " << full_path << std::endl;
        return;
    }

    std::istringstream header_stream(header);
    int width = 0, height = 0, ncolors = 0;
    header_stream >> width >> height >> ncolors;

    std::cout << "Image is " << width << " x " << height << " with " << ncolors << " colors" << std::endl;

    if (width == 0 || height == 0 || ncolors == 0) {
        std::cerr << "Invalid image dimensions or color count: " << width << " x " << height << ", " << ncolors << " colors" << std::endl;
        return;
    }

    read_image_colors(image_file_stream, ncolors);
    read_image_pixels(image_file_stream, width, height);

    this->width = width;
    image_file_stream.close();
}

std::string ImageRenderer::get_resource_path(const std::string &subdirectory, const std::string &file_name)
{
    std::filesystem::path base_path = std::filesystem::current_path();
    std::filesystem::path full_path = base_path / subdirectory / file_name;
    return full_path.string();
}



// Task R6: Reading the colors
//
// Implement the function for reading the color definitions of an
// image. As a reminder, the following is an example of the color definitions that the function should read
// w red
// . white
// + dark_cyan
// @ cyan
//
// dark_yellow
// The image file stream is passed in the image_file_stream
// parameter and the number of colors to be read are passed in the
// ncolors parameter. When the function is called,
// image_file_stream points to the beginning of the colors section
// of the file (assuming you implemented the previous task
// correctly). For every color definition read, call the function
// add_color to add the color to the internal representation. The
// add_color function takes two parameters: a char containing the
// color reference and a string containing the color
// name.
void ImageRenderer::read_image_colors(ifstream &image_file_stream, int ncolors)
{
  // BEGIN: R6
  std::string line;
  for(int i = 0; i < ncolors; ++i) {
    if (std::getline(image_file_stream, line)) {
      std::istringstream iss(line);
      std::string color;
      char ref;
      if (iss >> ref >> color) {
        add_color(ref, color);
        std::cout << "Added color: " << ref << " -> " << color << std::endl;
      }
    }
  }
  // END: R6
}


// Task R7: Reading the pixels
//
// Implement the function for reading the pixels part of the image. From
// the width and height variables initialized in the read_image
// function, you know the dimensions of the image and therefore the
// number of lines of image data to read and the number of characters
// each line has. For every line you read, make a call to the add_line
// function without arguments. For every pixel you read, call the
// add_pixel function with the name of the color of the pixel. The
// mappings between color references and values are stored in the map
// colors. Thus, you can use the color reference char you read from the
// image file to perform a lookup in the colors map to get the needed
// argument to the add_pixel function.

void ImageRenderer::read_image_pixels(ifstream &image_file_stream, int width, int height)
{
  // BEGIN: R7
  for(int h = 0; h < height; ++h) {
    std::string line;
    if (std::getline(image_file_stream, line)) {
      add_line(); // Legg til ny linje i bildet
      for(int w = 0; w < width; ++w) {
        char pixel_ref = line[w];
        add_pixel(colors.at(pixel_ref)); // Legg til piksel til den siste linjen i bildet
      }
    }
  }
  // END: R7
}


void ImageRenderer::draw_image()
{
  int cur_x = x;
  int cur_y = y;

  for (auto &row : image) {
    for (auto color : *row) {
      draw_pixel({cur_x, cur_y}, color);
      cur_x += 1; // Flytt til neste piksel horisontalt
    }
    cur_y++; // Flytt til neste linje vertikalt
    cur_x = x; // Tilbakestill x-posisjonen for ny linje
  }
}


ImageRenderer::ImageRenderer(AnimationWindow &window, int x, int y,
                             string file_name)
    : window(window), x{x}, y{y}
{
  read_image(get_resource_path("symbols", file_name + ".sxpm"));
}

void ImageRenderer::draw_pixel(TDT4102::Point point, TDT4102::Color color)
{
  auto [x, y] = point;
  window.draw_line({x, y}, {x + 1, y}, color);
}

