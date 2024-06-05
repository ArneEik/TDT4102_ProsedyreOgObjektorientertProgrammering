#pragma once
#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "cardDeck.h" 

class Blackjack {
private:
    CardDeck deck; // Kortstokken som brukes i spillet
    std::vector<Card> playerHand; // Spillerens hånd
    std::vector<Card> dealerHand; // Dealerens hånd
    int playerHandSum; // Summen av verdiene til spillerens hånd
    int dealerHandSum; // Summen av verdiene til dealerens hånd

    bool isAce(const Card& card);
    int getCardValue(const Card& card);
    int getHandScore(const std::vector<Card>& hand);
    void drawPlayerCard();
    void drawDealerCard();
    bool askPlayerDrawCard();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
    void showHands(bool showDealerAllCards);
    void playMore();

public:
    Blackjack(); // Konstruktør som initialiserer spillet
    
    void playGame(); // Metode for å starte og kjøre spillet

    // Eventuelle andre hjelpefunksjoner som trengs for spilllogikken
};