#include "include.h"


void Mastermind::playMastermind() {
    constexpr int size = 4;
    constexpr int letters = 6;
    constexpr int maxAttempts = 6; 
    // Generer tilfeldig kode
    string code = utils.randomizeString(size, 'A', 'A' + letters - 1);

    int attempts = 0;
    bool isGameWon = false;

    // Spill-løkke
    while (attempts < maxAttempts && !isGameWon) {
        cout<<"du har "<< maxAttempts - attempts<<" forsøk igjen"<<endl;
        string guess = utils.readInputToString(size, 'A', 'F');

        int correctPositions = checkCharactersAndPosition(code, guess);
        cout << "Du har " << correctPositions << " bokstaver riktig plassert." << endl;

        int correctCharacters = checkCharacters(code, guess);
        cout << "Du har " << correctCharacters << " riktige bokstaver." << endl;

        attempts++;
        if (correctPositions == size) {
            isGameWon = true;
            cout << "Gratulerer, du har gjettet koden!" << endl;
        }
    }

    // Håndter spillslutt
    if (!isGameWon) {
        cout << "Du har brukt opp dine forsøk. Bedre lykke neste gang!" << endl;
    }

    // Spør om å spille igjen
    char playAgain;
    cout << "Vil du spille igjen? (Y/N): ";
    cin >> playAgain;
    if (toupper(playAgain) == 'Y') {
        playMastermind(); // Rekursivt kall for å starte spillet på nytt
    }
}
int Mastermind::checkCharactersAndPosition(const string& code, const string& guess) {
    int correctCount = 0;

    for (size_t i = 0; i < code.length(); ++i) {
        if (code[i] == guess[i]) {
            correctCount++;
        }
    }

    return correctCount;
}
int Mastermind::checkCharacters(const string& code, const string& guess) {
    int correctCharacters = 0;

    for (char ch = 'A'; ch <= 'F'; ++ch) {
        int countInCode = utils.countChar(code, ch);
        int countInGuess = utils.countChar(guess, ch);

        correctCharacters += min(countInCode, countInGuess);
    }

    return correctCharacters;
}