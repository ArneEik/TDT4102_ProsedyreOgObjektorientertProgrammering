#include "include.h"

void Test::testRank(){
    Card::Rank r = Card::Rank::king;
    Card::Suit s = Card::Suit::hearts;
    string rank = Card::rankToString(r);
    string suit = Card::suitToString(s);
    cout << "Rank: " << rank << " Suit: " << suit << endl;
}
void Test::testCard(){
    Card c{Card::Suit::spades, Card::Rank::ace};
    cout << c.toString() << '\n';
}
void Test::testPrintCardDeck() {
    CardDeck deck; // Oppretter en ny kortstokk
    const auto& cards = deck.getCards(); // Henter kortene

    for (const auto& card : cards) {
        std::cout << card.toString() << std::endl; // Printer hvert kort
    }
}
void Test::testCardDeck() {
    CardDeck deck; // Oppretter en ny kortstokk
    deck.shuffle(); // Stokker kortstokken

    std::cout << "Trekker 5 kort fra stokken:" << std::endl;

    for (int i = 0; i < 53; ++i) {
        if (i < deck.getCards().size()) { // Sjekker om det er nok kort igjen i stokken
            Card drawnCard = deck.drawCard(); // Trekker et kort
            std::cout << "Trukket kort: " << drawnCard.toString() << std::endl;
        } else {
            std::cout << "Ikke nok kort igjen i stokken for å trekke flere." << std::endl;
            break;
        }
    }
}