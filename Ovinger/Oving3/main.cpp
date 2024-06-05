//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

// #include "std_lib_facilities.h"
#include "cannonball.h"
#include "oppgave3.h"
#include "utilities.h"
#include <cmath>
Cannonball cb;
Oppgave3 o3;
Utilities ut;
// const double initVelocityY {20};
// const double maxError{1e-3};

//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main() {
    bool close{false};
    string pick;
    while (!close) {
        cout << "Wanna play a game? (Y/N) ";
        cin >> pick;
        if (pick == "N" || pick == "n") {
            close = true;
        } else if (pick == "Y" || pick == "y") {
            cb.playTargetPractice(); 
        } else {
            cout << "Invalid input. Please enter Y or N: ";
        }
    }
    return 0;
}
//------------------------------------------------------------------------------

