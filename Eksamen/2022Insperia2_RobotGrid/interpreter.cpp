#include "interpreter.h"


// Task S1: Color name mapping
//
// This function takes the name of a color as its argument and
// returns the corresponding Graph_lib color type. This function is
// needed to convert the color names given as strings in the
// instruction code to the internal color representation used by the
// graphics library. We provide the map color_map, defined in
// interpreter.h that contains all valid mappings between color
// names and color types.
Color Interpreter::get_color(string color_name) 
{
  // BEGIN: S1
  //
  // Write your answer to assignment S1 here, between the // BEGIN: S1
  // and // END: S1 comments. You should remove any code that is
  // already there and replace it with your own.

  return color_map.at(color_name);

  // END: S1
}

// Task S2: Instruction interpretation
//
// The interpreter function Interpreter::execute_instruction()
// reads an instruction (refer to the table in the
// assignment PDF for a description) and calls the corresponding
// function in the RobotGrid class to perform the requested action
// for changing the universe
void Interpreter::execute_instruction(istringstream instruction)
{
  // BEGIN: S2
  //
  // Write your answer to assignment S2 here, between the // BEGIN: S2
  // and // END: S2 comments.
  // You may use the code below as a starting point for your
  // implementation following the structure of the implementation of
  // the make_grid command or you may start from scratch. If you use
  // this code as a starting point, replace each of the throw
  // string("Not implemented " + cmd); lines with your implementation.

  string instr;
  instruction >> instr;
  if (instr == "make_grid") {
    int rows;
    int cols;

    instruction >> rows;
    instruction >> cols;

    grid.make_grid(rows, cols);

  } else if (instr == "make_robot") {
    std::string name;
    int x, y;
    std::string color_name;

    instruction >> name >> x >> y >> color_name;
    TDT4102::Point pos = {x, y};
    TDT4102::Color color = get_color(color_name);

    grid.make_robot(name, pos, color);
  } else if (instr == "clear_robots") {
    grid.clear_robots();
  } else if (instr == "move_robot") {
    std::string name;
    int x, y;

    instruction >> name >> x >> y;
    TDT4102::Point pos = {x, y};
    grid.move_robot(name, pos);
  } else if (instr == "recolor_robot") {
    std::string name;
    std::string color_name;

    instruction >> name >> color_name;
    TDT4102::Color color = get_color(color_name);
    grid.recolor_robot(name, color);
  } else if (instr == "rename_robot") {
    std::string name;
    std::string new_name;

    instruction >> name >> new_name;
    grid.rename_robot(name, new_name);
  } else if (instr == "delete_robot") {
    std::string name;

    instruction >> name;
    grid.delete_robot(name);
  } else {
    // Don't change this
    throw string("Invalid command " + instr);
  }


  // END: S2
}

// |
// | END OF ASSIGNMENTS
// |

Interpreter::Interpreter(RobotGrid &grid) : grid(grid) 
{
}
