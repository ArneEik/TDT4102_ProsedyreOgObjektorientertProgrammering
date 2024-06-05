//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor


//------------------------------------------------------------------------------'
#include <iostream>
#include <cassert>
#include "minne.h"
#include "matrix.h"
#include "dummy.h"
void dummyTest() {
Dummy a;
*a.num = 4;
Dummy b{a};
Dummy c;
c = a;
std::cout << "a: " << *a.num << '\n';
std::cout << "b: " << *b.num << '\n';
std::cout << "c: " << *c.num << '\n';
*b.num = 3;
*c.num = 5;
std::cout << "a: " << *a.num << '\n';
std::cout << "b: " << *b.num << '\n';
std::cout << "c: " << *c.num << '\n';
}





// C++ programs start by executing the function main
int main() {
    // Show a nice message in the Terminal window

    // lagfib();
    Matrix m{3};
    std::cout<<m<<std::endl;

    Matrix a{3,3};
    Matrix b{3,3};
    b+= a;
    Matrix c{3,3};
    std::cout<<a<<b<<c;
    c += a + b;

    std::cout<<a<<b<<c;

    return 0;
}

//------------------------------------------------------------------------------
