#include "AnimationWindow.h"
#include "Emoji.h"

// Definer størrelse på vindu og emoji
constexpr int xmax = 1000;
constexpr int ymax = 600;
constexpr int emojiRadius = 50;

int main() {
    const Point tl{100, 100};
    const string win_label{"Emoji factory"};
    constexpr int xmax = 1000;
    constexpr int ymax = 600;
    

    Point faceCentre{xmax / 2, ymax / 2};
    int faceRadius = 100; 
    int eyeRadius = 20; 
    bool go = true;


    while (go){
        cout << "Velg en emoji å tegne:\n";
        cout << "1: Smile\n";
        cout << "2: Sad\n";
        cout << "3: Angry\n";
        cout << "4: Wink\n";
        cout << "5: Surprised\n";
        cout << "6: Cry\n";
        cout << "7: Shake\n";
        cout << "8: Sun\n";
        cout << "Ditt valg (0 for aa avslutte): ";
        int choice;
        cin >> choice;
        
        AnimationWindow win{tl.x, tl.y, xmax, ymax, win_label};
        
        switch (choice) {
            case 0:
            {
                go = false;
                break;
            }
            case 1:
                {
                    SmileFace smile{faceCentre, faceRadius, eyeRadius};
                    smile.draw(win);
                    break;
                }
            case 2:
                {
                    SadFace sad{faceCentre, faceRadius, eyeRadius};
                    sad.draw(win);
                    break;
                }
            case 3:
                {
                    AngryFace angry{faceCentre, faceRadius, eyeRadius};
                    angry.draw(win);
                    break;
                }
            case 4:
                {
                    WinkFace wink{faceCentre, faceRadius, eyeRadius};
                    wink.draw(win);
                    break;
                }
            case 5:
                {
                    SurprisedFace surprised{faceCentre, faceRadius, eyeRadius};
                    surprised.draw(win);
                    break;
                }
            case 6:
                {
                    CryFace cry{faceCentre, faceRadius, eyeRadius};
                    cry.draw(win);
                    break;
                }
            case 7:
                {
                    ShakingFace shake{faceCentre, faceRadius, eyeRadius};
                    shake.draw(win);
                    break;
                }
                        
            case 8:
                {
                    SunglacessesFace sun{faceCentre, faceRadius, eyeRadius};
                    sun.draw(win);
                    break;
                }

case 9:
{
    // Beregn plassering for hver emoji
    int horizontalSpacing = xmax / 5;  // Horisontal avstand mellom emojiene
    int verticalSpacing = ymax / 4;    // Vertikal avstand mellom emojiene
    int currentX = horizontalSpacing;  // Startposisjon for X
    int currentY = verticalSpacing;    // Startposisjon for Y

    // Opprett og tegn hver emoji med et unikt sentrum
    SmileFace smile{{currentX, currentY}, faceRadius, eyeRadius};
    smile.draw(win);
    currentX += horizontalSpacing;

    SadFace sad{{currentX, currentY}, faceRadius, eyeRadius};
    sad.draw(win);
    currentX += horizontalSpacing;

    AngryFace angry{{currentX, currentY}, faceRadius, eyeRadius};
    angry.draw(win);
    currentX += horizontalSpacing;

    WinkFace wink{{currentX, currentY}, faceRadius, eyeRadius};
    wink.draw(win);
    // Tilbakestill X og flytt ned for å starte en ny rad
    currentX = horizontalSpacing;
    currentY += verticalSpacing;

    SurprisedFace surprised{{currentX, currentY}, faceRadius, eyeRadius};
    surprised.draw(win);
    currentX += horizontalSpacing;

    CryFace cry{{currentX, currentY}, faceRadius, eyeRadius};
    cry.draw(win);
    currentX += horizontalSpacing;

    ShakingFace shake{{currentX, currentY}, faceRadius, eyeRadius};
    shake.draw(win);
    currentX += horizontalSpacing;

    // Antar at SunglassesFace er riktig implementert
    SunglacessesFace sun{{currentX, currentY}, faceRadius, eyeRadius};
    sun.draw(win);

    break;
}

            default:
                cout << "Ugyldig valg.\n";
        }

        if(go){win.wait_for_close();}
    }
    return 0;
}