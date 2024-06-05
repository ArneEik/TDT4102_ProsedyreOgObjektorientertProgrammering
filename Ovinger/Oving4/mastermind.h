#pragma once

class Mastermind{
public:
    void playMastermind();
    int checkCharactersAndPosition(const string& code, const string& guess);
    int checkCharacters(const string& code, const string& guess);
};