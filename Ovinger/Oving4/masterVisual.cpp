#include "masterVisual.h"
#include "include.h"
// MastermindWindow m;
Guess g;

void playMastermindVisual() {
    constexpr int size = 4;
    constexpr int letters = 6;
    constexpr int maxAttempts = 6; 

    string code = utils.randomizeString(size, 'A', 'A' + letters - 1);

    int attempts = 0;
    bool isGameWon = false;
    MastermindWindow mwin{900, 20, winW, winH, size, "Mastermind"};

    // Viser den hemmelige koden for debugging
    mwin.setCodeHidden(true);
    addGuess(mwin, code, 'A'); 

    while (attempts < maxAttempts && !isGameWon) {
        cout<< "du har " << maxAttempts - attempts << " forsøk igjen" << endl;
        string guess = mwin.getInput(size, 'A', 'F');

        addGuess(mwin, guess, 'A'); // Legger til brukerens gjett

        int correctPositions = master.checkCharactersAndPosition(code, guess);
        cout << "Du har " << correctPositions << " bokstaver riktig plassert." << endl;

        int correctCharacters = master.checkCharacters(code, guess);
        cout << "Du har " << correctCharacters << " riktige bokstaver." << endl;

        addFeedback(mwin, correctPositions, correctCharacters - correctPositions);
        mwin.drawGuessesAndFeedbacks(); // Tegner gjett og tilbakemeldinger
        
        if (correctPositions == size) {
            mwin.setCodeHidden(true);
            cout << "Gratulerer, du har gjettet koden!" << endl;
            addFeedback(mwin, correctPositions, correctCharacters - correctPositions);
            mwin.drawGuessesAndFeedbacks(); // Tegner gjett og tilbakemeldinger
             
            isGameWon = true;  // Spillet er vunnet

        }
        attempts++;

    }

    if (!isGameWon) {
        mwin.setCodeHidden(false);
        mwin.drawGuessesAndFeedbacks(); // Tegner gjett og tilbakemeldinger
        cout << "Du har brukt opp dine forsøk. Bedre lykke neste gang!" << endl;
    }

    // Viser den hemmelige koden og holder vinduet åpent
    mwin.drawGuessesAndFeedbacks();
    mwin.setCodeHidden(false); // Avslører den hemmelige koden
    mwin.wait_for_close(); 
    // Spør om å spille igjen
    char playAgain;
    cout << "Vil du spille igjen? (Y/N): ";
    cin >> playAgain;
    if (toupper(playAgain) == 'Y') {
        mwin.setCodeHidden(true); // Avslører den hemmelige koden
        playMastermindVisual(); // Rekursivt kall for å starte spillet på nytt
    }
}


void addGuess(MastermindWindow &mwin, const string Code, const char startLetter)
{
    Guess newGuess = {Code, startLetter};
    mwin.guesses.push_back(newGuess);
}

void addFeedback(MastermindWindow &mwin, const int correctPosition, const int correctCharacter)
{
    Feedback newFeedback = {correctPosition, correctCharacter};
    mwin.feedbacks.push_back(newFeedback);
}

void MastermindWindow::drawCodeHider()
{
	if (code_hidden) {
		draw_rectangle(Point{padX, 3 * padY}, winW - size * padX, padY*2, Color::black);
	}
}

MastermindWindow::MastermindWindow(int x, int y, int w, int h, int size, const string &title) 
: AnimationWindow(x, y, w, h, title),

guessBtn{{upperLeftCornerBtn.x, upperLeftCornerBtn.y}, btnW, btnH, "Add"},
guess{{upperLeftCornerInBox.x, upperLeftCornerInBox.y}, inBoxW, inBoxH, ""},
size(size)
{    cout << "MastermindWindow-konstruktør kalt." << endl;

	add(guess);
	add(guessBtn);
	guessBtn.setCallback(std::bind(&MastermindWindow::cb_guess, this));
};

void MastermindWindow::drawGuessesAndFeedbacks(){
	std::map<int, Color> colorConverter{
		{1, Color::red},
		{2, Color::green},
		{3, Color::yellow},
		{4, Color::blue},
		{5, Color::blue_violet},
		{6, Color::dark_cyan}};
    bool showWinAnimation = false;	

    for (int guessIndex = 0; guessIndex < static_cast<int>(guesses.size()); ++guessIndex) {
        int xPos = padX;
        int yPos = padY * (2 * guessIndex + 3);

        for (char c : guesses[guessIndex].code) {
            int colorValue = c - 'A' + 1;
            try {
                Color fillColor = colorConverter.at(colorValue);
                draw_rectangle({xPos, yPos}, padX, padY, fillColor, Color::black);
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of Range error: " << e.what() << " with colorValue: " << colorValue << std::endl;
            }

            xPos += 2 * padX;
        }
    }

    for (int i = 0; i < 6; ++i) {
        char letter = 'A' + i;
        int colorValue = letter - 'A' + 1;
        Color fillColor = colorConverter.at(colorValue);
        draw_rectangle({padX * (i + 1), winH - padY}, padX, padY, fillColor, Color::black);
        draw_text({padX * (i+1) + padX / 2, winH - padY}, std::string(1, letter), Color::black);
    }

        for (int feedbackIndex = 0; feedbackIndex < static_cast<int>(feedbacks.size()); ++feedbackIndex) {
            int xPos = padX*9 + feedbackIndex;
            int yPos = padY * 3.5 + (padY * 2 * (feedbackIndex+1));

            int redCircles = 0;
            int totalCircles = feedbacks[feedbackIndex].correctPosition + feedbacks[feedbackIndex].correctCharacter;
            
            for (int i = 0; i < totalCircles; ++i) {
                Color circleColor = (i < feedbacks[feedbackIndex].correctPosition) ? Color::red : Color::black;
                if (circleColor == Color::red) {
                    redCircles++;
                }
                draw_circle({xPos, yPos}, radCircle, circleColor);
                xPos += 2 * radCircle;
            }

            // Sjekk om det er fire røde sirkler
            if (redCircles == 4) {
                showWinAnimation = true;
            }
        }
        if (showWinAnimation) {
            string text = "U won!!!";
            int xPost = 100; 
            int yPos = 200;
            for (int j = 0; j < 325; j++) {
                int fontSize = 40 + static_cast<int>(15 * sin(j * M_PI / 30));
                MastermindWindow::draw_text(Point{xPost, yPos}, text, Color::red, fontSize, Font::courier_bold_italic);
                MastermindWindow::next_frame();
        }
    }

}


string MastermindWindow::wait_for_guess()
{

	while (!button_pressed && !should_close())
	{
		drawGuessesAndFeedbacks();
		// Burde tegnes sist siden den skal ligge på toppen
		drawCodeHider();

		next_frame();
	}
	button_pressed = false;

	string newGuess = guess.getText();
	guess.setText("");

	return newGuess;
}

string MastermindWindow::getInput(unsigned int n, char lower, char upper)
{
	bool validInput = false;
	string guess;
	while (!validInput && !should_close())
	{
		guess.clear();
		string input = wait_for_guess();
		if (input.size() == n)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				char ch = input.at(i);
				if (isalpha(ch) && toupper(ch) <= upper && lower <= toupper(ch))
				{
					guess += toupper(ch);
				}
				else
					break;
			}
		}
		if (guess.size() == n)
		{
			validInput = true;
		}
		else
		{
			cout << "Invalid input guess again" << endl;
		}
	}
	return guess;
}

void MastermindWindow::setCodeHidden(bool hidden) {
	code_hidden = hidden;
}
