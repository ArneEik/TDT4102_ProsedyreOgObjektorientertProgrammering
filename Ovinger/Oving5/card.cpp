#include "include.h"

string Card::suitToString(Card::Suit suit) {
    static const map<Suit, string> suitMap = {
        {clubs, "Clubs"},
        {diamonds, "Diamonds"},
        {hearts, "Hearts"},
        {spades, "Spades"}
    };

    auto it = suitMap.find(suit);
    if (it != suitMap.end()) {
        return it->second;
    } else {
        return "Unknown Suit";
    }
}
string Card::rankToString(Card::Rank rank) {
    static const map<Rank, string> rankMap = {
        {two, "Two"},
        {three, "Three"},
        {four, "Four"},
        {five, "Five"},
        {six, "Six"},
        {seven, "Seven"},
        {eight, "Eight"},
        {nine, "Nine"},
        {ten, "Ten"},
        {jack, "Jack"},
        {queen, "Queen"},
        {king, "King"},
        {ace, "Ace"}
    };

    auto it = rankMap.find(rank);
    if (it != rankMap.end()) {
        return it->second;
    } else {
        return "Unknown Rank";
    }
}
Card::Card(Suit suit, Rank rank) : s(suit), r(rank){}

Card::Suit Card::getSuit() const {
    return s;
}
Card::Rank Card::getRank() const {
    return r;
}
string Card::toString() const {
    string rank, suit;
    // Konverter Rank til streng
    switch (r) {
        case two: rank = "Two"; break;
        case three: rank = "Three"; break;
        case four: rank = "Four"; break;
        case five: rank = "Five"; break;
        case six: rank = "Six"; break;
        case seven: rank = "Seven"; break;
        case eight: rank = "Eight"; break;
        case nine: rank = "Nine"; break;
        case ten: rank = "Ten"; break;
        case jack: rank = "Jack"; break;
        case queen: rank = "Queen"; break;
        case king: rank = "King"; break;
        case ace: rank = "Ace"; break;
        default: rank = "Unknown Rank";
    }
    // Konverter Suit til streng
    switch (s) {
        case clubs: suit = "Clubs"; break;
        case diamonds: suit = "Diamonds"; break;
        case hearts: suit = "Hearts"; break;
        case spades: suit = "Spades"; break;
        default: suit = "Unknown Suit";
    }
    return rank + " of " + suit; 
}