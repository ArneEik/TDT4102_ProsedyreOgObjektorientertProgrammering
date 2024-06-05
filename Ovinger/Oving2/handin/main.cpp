//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

#include "include.h"

int main() {

int pick;
bool validPick = false;
Oppgave1 Oppgave1;
Oppgave2 Oppgave2;
Oppgave3 Oppgave3;
Oppgave4 Oppgave4;
Oppgave5 Oppgave5;

while (!validPick) {
    cout << "Velg oppgavegruppe: \n"
            << "0) Avslutt\n"
            << "1) Oppgave 1\n"
            << "2) Oppgave 2\n"
            << "3) Oppgave 3\n"
            << "4) Oppgave 4\n"
            << "5) Oppgave 5\n"
            << "Angi valg (0-5): ";
    cin >> pick;
    switch (pick) {
        case 0:
            cout << "Du har avsluttet\n";
            validPick = true;
            break;
        case 1:
            Oppgave1.chooseTask();
            break;
        case 2:
            Oppgave2.chooseTask(); 
            break;
        case 3:
            Oppgave3.chooseTask(); 
            break;
        case 4:
            Oppgave4.chooseTask(); 
            break;
        case 5:
            Oppgave5.chooseTask(); 
            break;
        default:
            cout << "Ikke gyldig valg, prøv igjen\n";
            break;
    }
}
return 0;
}


//------------------------------------------------------------------------------
