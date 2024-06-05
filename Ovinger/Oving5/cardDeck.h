#pragma once
#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "card.h"
class CardDeck{
private:
    vector<Card> cards;

public: 
    CardDeck();
//public no for testing
    void swap(int index1, int index2); // Uten spesifikke krav, ville en typisk tilnærming være å gjøre swap() private og kun eksponere den gjennom andre public metoder som utfører høyere nivå operasjoner (som å blande kortstokken), for å opprettholde en god grad av innkapsling og kontroll.
    static void printCardDeck();
    void shuffle();
    Card drawCard(); 

    const vector<Card>& getCards() const { return cards; }

};