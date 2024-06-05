#include "include.h"

CardDeck::CardDeck() {
    for (int suit = Card::clubs; suit <= Card::spades; ++suit) {
        for (int rank = Card::two; rank <= Card::ace; ++rank) {
            cards.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
        }
    }
}

void CardDeck::swap(int index1, int index2) {
    if (abs(index1) < cards.size() && abs(index2) < cards.size()){
        std::swap(cards[index1], cards[index2]);
    }
}
void CardDeck::printCardDeck() {
    CardDeck deck; 
    const auto& cards = deck.getCards(); 

    for (const auto& card : cards) {
        std::cout << card.toString() << std::endl; 
    }
}
void CardDeck::shuffle() {
    // Oppretter en tilfeldig tallgenerator
    std::random_device rd;  // Vil bli brukt til å oppnå en seed for tilfeldighet
    std::mt19937 g(rd());   // Initialiserer Mersenne Twister-generator med seed fra rd

    // Bruker std::shuffle for å stokke kortene i 'cards'-vektoren
    std::shuffle(cards.begin(), cards.end(), g);
}
Card CardDeck::drawCard() {
    if (cards.empty()) {
        throw std::runtime_error("Cannot draw from an empty deck.");
    }
    Card drawnCard = cards.back(); // Henter det siste kortet
    cards.pop_back(); // Fjerner det siste kortet fra vektoren
    return drawnCard; // Returnerer det trukne kortet
}
