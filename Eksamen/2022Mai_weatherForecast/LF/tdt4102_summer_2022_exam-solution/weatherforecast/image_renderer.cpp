#include "image_renderer.h"
#include "AnimationWindow.h"
#include "util.h"
#include <filesystem>
#include <memory>
#include <sstream>
#include <stdexcept>

// Task R1: Color lookup
//
// Write a function that returns the Graph_lib
// color type corresponding to the color name given in the parameter
// color. To do this, you may use the map color_map defined in
// image_renderer.h. If the parameter color refers to an invalid
// color the function should throw an exception.
Graph_lib::Color::Color_type ImageRenderer::get_color_value(string color)
{
  // BEGIN: R1
  if (color_map.count(color)) {
    return color_map[color];
  } else {
    throw runtime_error("Invalid color name " + color);
  }
  // END: R1
}

// Task R2: Add color references
//
// Write a function that given a color reference (parameter ref)
// and a color name (parameter color_name) adds an entry to the
// colors-map. Use the function get_color_value to look up the
// color names.
void ImageRenderer::add_color(char ref, string color_name)
{
  // BEGIN: R2
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
  image.push_back(make_unique<vector<Graph_lib::Color::Color_type>>());
  // END: R3
}

// Task R4: Add image pixels
//
// Write a function that adds a pixel to the image. Since the image
// data is read line-by-line, always add the pixel to the most
// recently added vector in the image vector.
void ImageRenderer::add_pixel(Graph_lib::Color::Color_type color)
{
  if (image.size() == 0) {
    throw runtime_error(
        "Remember to insert a call to the add_line funtion for every image "
        "line you read in the read_image_pixels function");
  }

  // BEGIN: R4
  image.back()->push_back(color);
  // END: R4
}

// Task R5: Reading the header
//
// Complete the function for reading the image header. Most of the
// hard work is already done for you but the part for reading the
// actual values into the variables width, height, and ncolors
// is missing. Your task is to add this.
void ImageRenderer::read_image(string file_name)
{
  ifstream image_file_stream;

  image_file_stream.open(file_name, ifstream::in);

  string header;

  // Read the header line
  getline(image_file_stream, header);

  // Turn the header line into an istringstream
  istringstream header_stream(header);

  // The width of the image
  int width = 0;

  // The height of the image
  int height = 0;

  // The number of colors of the image
  int ncolors = 0;

  // BEGIN: R5
  header_stream >> width;
  header_stream >> height;
  header_stream >> ncolors;
  // END: R5

  // cout << "Image is " << width << " x " << height << " with " << ncolors
  //      << " colors" << endl;

  read_image_colors(image_file_stream, ncolors);
  read_image_pixels(image_file_stream, width, height);

  this->width = width;

  image_file_stream.close();
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
  for (int i = 0; i < ncolors; i++) {
    string color_def;
    getline(image_file_stream, color_def);
    istringstream color_def_stream(color_def);

    char ref;
    string color_name;

    color_def_stream >> ref;
    color_def_stream >> color_name;

    add_color(ref, color_name);
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
void ImageRenderer::read_image_pixels(ifstream &image_file_stream, int width,
                                      int height)
{
  // BEGIN: R7
  for (int i = 0; i < height; i++) {
    string img_line;
    getline(image_file_stream, img_line);
    add_line();
    for (int j = 0; j < width; j++) {
      add_pixel(colors[img_line[j]]);
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
      cur_x += 1;
    }
    cur_y++;
    cur_x = x;
  }
}

ImageRenderer::ImageRenderer(AnimationWindow &window, int x, int y,
                             string file_name)
    : window(window), x{x}, y{y}
{
  read_image(get_resource_path("symbols", file_name + ".sxpm"));
}

void ImageRenderer::draw_pixel(Point point, Graph_lib::Color::Color_type color)
{
  auto [x, y] = point;
  window.draw_line({x, y}, {x + 1, y}, color);
}

