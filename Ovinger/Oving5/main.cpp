//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor
#include"include.h"
Test test;
Blackjack play;

int main() {
    int valg;

    while (true) {
        cout << "Meny:\n";
        cout << "1. Test Rank\n";
        cout << "2. Test Card \n";
        cout << "3. Print Card deck \n";
        cout << "4. Test Card deck \n";
        cout << "5. play BlackJack \n";
        cout << "0. Avslutt\n";
        cout << "Velg et alternativ (1-5): ";
        cin >> valg;

        switch (valg) {
            case 1:
                cout << "Du valgte alternativ 1.\n\n";
                test.testRank();
                break;
            case 2:
                cout << "Du valgte alternativ 2.\n\n";
                test.testCard();
                break;
            case 3:
                cout << "Du valgte alternativ 3.\n";
                test.testPrintCardDeck();
                break;
            case 4:
                cout << "Du valgte alternativ 4.\n";
                test.testCardDeck();
                break;
            case 5:
                cout << "Du valgte alternativ 5.\n";
                play.playGame();
                break;
            case 0:
                cout << "Avslutter programmet.\n";
                return 0;
            default:
                cout << "Ugyldig valg, prøv igjen.\n";
                break;
        }cout<<"\n-------------------------------------------------\n";
    }

    return 0;
}

//------------------------------------------------------------------------------
