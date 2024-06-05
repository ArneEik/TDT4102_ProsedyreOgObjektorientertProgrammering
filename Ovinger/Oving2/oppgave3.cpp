#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "oppgave3.h"


double Oppgave3::discriminant(double a, double b, double c) {
    return pow(b, 2) - 4 * a * c;
}

void Oppgave3::printRealRoots(double a, double b, double c) {
    Oppgave3 Oppgave3;
    double disc = Oppgave3.discriminant(a, b, c);
        if (disc > 0) {
            // To reelle løsninger
            double root1 = (-b + sqrt(disc)) / (2 * a);
            double root2 = (-b - sqrt(disc)) / (2 * a);
            cout << "To reelle losninger: " << root1 << " og " << root2 << endl;
        } else if (disc == 0) {
            // Én reell løsning
            double root = -b / (2 * a);
            cout << "Én reell losning: " << root << endl;
        } else {
            // Ingen reelle løsninger
            cout << "Ingen reelle losninger." << endl;
        }
}
void Oppgave3::solveQuadraticEquation(){
    Oppgave3 Oppgave3;
    //verdia for a b c
    double a;
    double b;
    double c;
    cout<< "skriv verdia for a b og c i ax2 + bx + c = 0\n";
    cout<< "skriv for a: ";
    cin>> a;
    cout<<endl;
    cout<< "skriv for b: ";
    cin>> b;
    cout<<endl;
    cout<< "skriv for c: ";
    cin>> c;
    cout<<endl;
    Oppgave3.printRealRoots(a,b,c);
}
void Oppgave3::chooseTask() {
    int pick;
    bool validPick = false;

    while (!validPick) { 
        cout << "Velg funksjon: \n"
             << "0) Tilbake\n"
             << "1) solveQuadraticEquation\n"
             << "Angi valg (0-1): ";
        cin >> pick;

        switch (pick) {
            case 0:
                validPick = true;
                break;
            case 1:
                Oppgave3::solveQuadraticEquation();
                break;
            default:
                cout << "Ikke gyldig valg, prøv igjen\n";
                break;
        }
    }
}

