//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

#include "include.h"
Tests tests;
Utilities utils;
Student student;
Mastermind master;


//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main() {
    bool close{false};
    string pick;
    while (!close) {
        cout << "MENU \n "
        <<"Oppgave 1.c\n "
        <<"Oppgave 1.d\n "
        <<"Oppgave 1.e\n "
        <<"Oppgave 2.d\n "
        <<"Oppgave 3\n "
        <<"Oppgave 4\n "
        <<"Oppgave 5\n "
        <<"Velg oppgave (nr.bokstav) eller N for aa avslutte: ";
        cin >> pick;
       // cout <<"\n\n";
        if (pick == "N" || pick == "n") {
            close = true;
        } else if (pick == "1.C" || pick == "1.c") {
            tests.testCallByValue();
        } else if (pick == "1.D" || pick == "1.d") {
            tests.testCallByReference();
        } else if (pick == "1.E" || pick == "1.e") {
            tests.testSwapAB();
        } else if (pick == "2.D" || pick == "2.d") {
            Student student1 = utils.createStudent("Adrian", "BIAIS", 23);
            utils.printStudent(student1);
            cout<<boolalpha<<utils.isInProgram(student1, "BIAIS")<<endl;
        } else if (pick == "3" || pick == "3") {
            tests.testString();
        } else if (pick == "4" || pick == "4") {
            master.playMastermind();
        }else if (pick == "5" || pick == "5") {
            playMastermindVisual();
        }else {
            cout << " Invalid input. ";
        }cout <<"\n\n";
    }
    return 0;
}
//-

//------------------------------------------------------------------------------
//1.a) programet vi skrive ut 
// << "v0: " 5
// << " increment: " 2
// << " iterations: " 10
// << " result: " 5+2*10=25

// 1.e)For å bytte om på to heltallvariablers verdi, er det mest effektivt å bruke referanser. 
// Dette er fordi referanser lar funksjonen direkte endre de opprinnelige verdiene av de 
// variablene som blir sendt inn til funksjonen. Hvis du bruker pass-by-value (verdi), vil 
// funksjonen kun bytte om på kopier av verdiene, og de opprinnelige variablene vil forbli 
// uendret. Pass-by-const-reference vil ikke tillate endring av verdiene i det hele tatt, 
// siden de er konstante referanser.

// 2.e) Feilmeldinga skyldes at definisjonen gjentas, noe som forårsaker feilmeldingen. 
// Dette kan skje hvis headerfilen inkluderes direkte eller indirekte (gjennom andre headerfiler) 
// flere ganger.
// Løysinga er å bruke includeGuards som #prgama once, eller  #ifndef, #define, og #endif

// 4.a) I spill som Mastermind, der visse verdier (som antall bokstaver eller lengden på koden) 
// er konstante og ikke skal endres gjennom spillets levetid, er constexpr ideelt fordi disse 
// verdiene er kjent ved kompileringstid og kan brukes i kompileringstidskontekster (som arraystørrelser). 