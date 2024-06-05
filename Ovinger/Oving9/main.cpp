//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Person.h"
#include "Car.h"
#include "MeetingWindow.h"
//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main() {
	unique_ptr<Car> car {new Car{0}};
    Person p4 {"p4", "p4@ntnu.no",move(car)};
    std::cout<<p4;
    MeetingWindow w(15,15,100,200,"lol");
    w.wait_for_close();
    return 0;
}

//------------------------------------------------------------------------------
