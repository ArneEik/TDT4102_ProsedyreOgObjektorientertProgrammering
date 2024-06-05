#pragma once
#include "subprojects\std_lib_facilities\std_lib_facilities.h"

class Card {
public:
    enum Suit {
        clubs,
        diamonds,
        hearts,
        spades
    };
    enum Rank {
        two = 2,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack = 11,
        queen = 12,
        king = 13,
        ace = 14
    };
    static string suitToString(Suit suit);
    static string rankToString(Rank rank); 
    Card(Suit suit, Rank rank);//konstuktør
    Suit getSuit() const;
    Rank getRank() const;
    string toString() const; 

private:
    Suit s;
    Rank r;
};