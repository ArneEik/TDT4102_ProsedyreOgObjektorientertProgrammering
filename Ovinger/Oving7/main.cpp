//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

// 1.a) Public : alle har tilgang, Private: kun klassen har tilgang, Protected : klasser som arver av klassen har tilgang.

// 1.d) Om du fjernar virtual nøkkelordet frå toString()-metoden i Animal-klassen, mister du polymorfien for denne metoden. Dette betyr at om du kallar toString() på ein peiker til Animal (som faktisk peiker til eit Cat eller Dog objekt), vil det alltid vere Animal sin versjon av toString() som blir kalla, ikkje den overstyrte versjonen i Cat eller Dog.

// 1.e) Når Animal-klassen er gjort abstrakt, vil forsøk på å opprette eit objekt av denne klassen resultere i ein kompileringsfeil. Dette er fordi kompilatoren ikkje kan instansiere ein abstrakt klasse


#include "std_lib_facilities.h"
#include "test.h"
#include "animal.h"

Test t;
//------------------------------------------------------------------------------'

// // C++ programs start by executing the function main
// int main() {
//     // Show a nice message in the Terminal window
//     cout << "Hello, World!" << endl;
//     t.testAnimal();

//     // This lets the operating system (Windows, Mac, Linux, etc.) know that the program
//     // did not encounter any errors
//     return 0;
// }

//------------------------------------------------------------------------------
