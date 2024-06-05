#include "util.h"

// Task {U1: Weekday numbers to names}
//
// Write a function that maps an integer between 0 and 6 to a weekday name. The first day of the week (value 0) is Monday. If the value of the weekday_num parameter is outside of that range, the function should throw an exception.
string format_weekday(int weekday_num)
{
  // BEGIN: U1

  switch (weekday_num) {
  case 0:
    return "Monday";
    break;
  case 1:
    return "Tuesday";
    break;
  case 2:
    return "Wednesday";
    break;
  case 3:
    return "Thursday";
    break;
  case 4:
    return "Friday";
    break;
  case 5:
    return "Saturday";
    break;
  case 6:
    return "Sunday";
    break;
  default:
    throw runtime_error("Invalid day number");
  }

  // END: U1
}

// Task U2: Friendly wind directions
//
// Write a function that bins the compass angles of wind directions (0 to 360) degrees to 8 different directions (e.g. North, Norh-West, etc.). If the value of the heading argument is outside of the valid range, the function should throw an exception.
//
// The mappings are as follows:
//
//
//  - 337.5 - 22.5:   North
//  - 292.5 - 337.5: North-West
//  - 247.5 - 292.5: West
//  - 202.5 - 247.5: South-West
//  - 157.5 - 202.5: South
//  - 112.5 - 157.5 South-East
//  - 67.5   - 112.5: East
//  - 22.5   - 67.5:   North-East
string format_wind_dir(double heading)
{
  // BEGIN: U2
  if ((heading >= 337.5 && heading <= 360) ||
      (heading >= 0 && heading <= 22.5)) {
    return "North";
  } else if (heading >= 292.5 && heading <= 337.5) {
    return "North-West";
  } else if (heading >= 247.5 && heading <= 292.5) {
    return "West";
  } else if (heading >= 202.5 && heading <= 247.5) {
    return "South-West";
  } else if (heading >= 157.5 && heading <= 202.5) {
    return "South";
  } else if (heading >= 112.5 && heading <= 157.5) {
    return "South-East";
  } else if (heading >= 67.5 && heading <= 112.5) {
    return "East";
  } else if (heading >= 22.5 && heading <= 67.5) {
    return "North-East";
  } else {
    throw runtime_error("Invalid heading " + to_string(heading));
  }
  // END: U2
}

// Task U3: Get unit as string
//
// Consider the enum Unit defined in util.h as
// follows
//
// enum Unit {
// UNIT_MS, // Meters per second, m/s
// UNIT_MM, // Millimeteres, mm
// UNIT_DC // Degrees celcius, °C
// };
//
// Write a function that given a Unit enum value returns the
// corresponding string representation. For example,
// get_unit(UNIT_MM) == "mm".
string get_unit(Unit unit)
{
  // BEGIN: U3
  switch (unit) {
  case UNIT_MS:
    return "m/s";
    break;
  case UNIT_MM:
    return "mm";
    break;
  case UNIT_DC:
    return "°C";
    break;
  }
  // END: U3
}

// Task U4: Format units
//
// Write a function that formats numeric weather parameters for
// presentation by rounding floating point numbers to a specified
// number of decimals and appending a unit. The function takes three
// parameters: The value to be formatted, the number of decimals
// that the value should be rounded to and the unit that should be
// appended to the formatted string. Use the function get_unit
// implemented in U3 to convert the unit value to a
// string.
//
// For example, the function should return values that makes the
// following comparisons true (assuming that the get_unit function
// is correctly implemented): format_value(3.94, 1, UNIT_MM) == "3.9
// mm" and format_value(3.587, 2, UNIT_MS) == "3.59
// m/s"
string format_value(double value, int decimals, Unit unit)
{
  // BEGIN: U4
  ostringstream sstr;
  sstr << setprecision(decimals) << fixed << value << ' ' << get_unit(unit);
  return sstr.str();

  // END: U4
}

// |
// | END OF ASSIGNMENTS
// |

string get_resource_path(string folder, string file)
{
  string file_path =
      (filesystem::path(string(__FILE__)).remove_filename() / folder / file)
          .string();

  return file_path;
}

