#include "include.h"
#include <chrono>
#include <thread>

Blackjack::Blackjack() : playerHandSum(0), dealerHandSum(0) {
    // Stokk kortstokken ved starten av spillet
    deck.shuffle();
}
bool Blackjack::isAce(const Card& card) {
    return card.getRank() == Card::ace;
}
int Blackjack::getCardValue(const Card& card) {
    switch (card.getRank()) {
        case Card::two: return 2;
        case Card::three: return 3;
        case Card::four: return 4;
        case Card::five: return 5;
        case Card::six: return 6;
        case Card::seven: return 7;
        case Card::eight: return 8;
        case Card::nine: return 9;
        case Card::ten:
        case Card::jack:
        case Card::queen:
        case Card::king:
            return 10;
        case Card::ace:
            return 11;
        default:
            throw runtime_error("Unknown card rank");
    }
}
int Blackjack::getHandScore(const vector<Card>& hand) {
    int score = 0;
    int aceCount = 0;

    // Først, legg sammen verdien av alle kort, og tell antall ess
    for (const Card& card : hand) {
        if (isAce(card)) {
            aceCount++;
            score += 11; // Først antar vi at ess er verdt 11
        } else {
            score += getCardValue(card);
        }
    }

    // Deretter, juster verdien av ess fra 11 til 1 hvis total poengsum overstiger 21
    while (score > 21 && aceCount > 0) {
        score -= 10; // Reduserer verdien av et ess fra 11 til 1
        aceCount--; // Et ess er justert
    }

    return score;
}
bool Blackjack::askPlayerDrawCard() {
    string response;
    cout << "Vil du trekke et nytt kort? (ja/nei): ";
    cin>> response;

    // Konverterer svaret til små bokstaver for enklere sammenligning
    // for (auto& c : response) {
    //     c = tolower(c);
    // }

    if (response == "ja") {
        return true;
    } else {
        return false;
    }
}
void Blackjack::drawPlayerCard() {
    Card drawnCard = deck.drawCard();
    playerHand.push_back(drawnCard);
    playerHandSum = getHandScore(playerHand);
}
void Blackjack::drawDealerCard() {
    Card drawnCard = deck.drawCard();
    dealerHand.push_back(drawnCard);
    dealerHandSum = getHandScore(dealerHand);
}
void Blackjack::playerTurn() {
    showHands(false); // Viser startkortene, med ett skjult dealer-kort if false
    bool draw = askPlayerDrawCard();
    if (playerHandSum < 21 && draw) {
        drawPlayerCard();
        cout << "Du trakk: " << playerHand.back().toString() << endl;
        cout << "Din poengsum: " << playerHandSum << endl;
        if (playerHandSum > 21) {
            cout << "Du tapte, poengsummen din overstiger 21.\n";
            return;
        }
    }
}

void Blackjack::dealerTurn() {
    while (dealerHandSum < 17) {
        drawDealerCard();
    }
    cout << "Dealerens poengsum: " << dealerHandSum << endl;
}
void Blackjack::determineWinner() {
    if (playerHandSum>21){
        cout << "Dealeren vinner.\n";
    }
    else if (dealerHandSum > 21 || playerHandSum > dealerHandSum) {
        cout << "Gratulerer, du vinner!\n";
    } else if (dealerHandSum == playerHandSum) {
        cout << "Det ble uavgjort.\n";
    } 
    else {
         cout << "Dealeren vinner.\n";
    }
}
void Blackjack::showHands(bool showDealerAllCards) {
    cout << "Dine kort: ";
    for (const auto& card : playerHand) {
        cout << card.toString() << " ";
    }
    cout << "(Total poengsum: " << playerHandSum << ")\n\n";

    cout << "Dealerens kort: ";
    if (showDealerAllCards) {
        for (const auto& card : dealerHand) {
            cout << card.toString() << " ";
        }
        cout << "(Total poengsum: " << dealerHandSum << ")\n\n";
    } else {
        cout << dealerHand[0].toString() << " [Skjult kort]\n\n";
    }
}
void Blackjack::playMore(){
    string play;
    cout<<"spele igjen? (ja/nei): ";
    cin>>play;
    if (play == "ja"){playGame();}
}
void Blackjack::playGame() {
    playerHand.clear();
    dealerHand.clear();
    playerHandSum = dealerHandSum = 0;

    deck.shuffle();
    cout << "Stokker kortene...\n\n";

    // Trekker startkortene
    drawPlayerCard();
    drawPlayerCard();
    drawDealerCard();
    drawDealerCard();

    // Spillerens tur
    playerTurn();

    // Sjekker om spilleren allerede har tapt
    if (playerHandSum <= 21) {dealerTurn();}

    determineWinner();
    playMore();
}

