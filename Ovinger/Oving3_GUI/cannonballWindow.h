#pragma once
#include "cannonball.h"
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"

class CannonballWindow : public AnimationWindow, Cannonball {
private:
    //Initial values
    static constexpr float KI = 0.011;
    static constexpr float KP = 0.05;
    static constexpr float tol = 0.01;
    static constexpr int fieldLength = 800;
    static constexpr int w_width = 1400;
    static constexpr int w_height = 700;
    static constexpr int timeSteps = 100;
    static constexpr TDT4102::Point wheelCenter ={50, w_height - 50};

    double theta_goal = 30.0;
    double current_theta = 800;
    double velocity = 80;
    double thetaIncrement = 0.1;
    double velocityIncrement = 0.1;

    std::vector<TDT4102::Point>missedShots{};

    //skytegreier
    double totalTime = 0.0;
    int totalFrames = 0;
    int fps = 5;
    double frameTime = 1.0 / fps; // Tid per frame i sekunder
    bool isShooting = false;
    double velX = velocity*cos(degToRad(theta_goal));
    double velY = velocity*sin(degToRad(theta_goal));
    double CannonballposX = 0;
    double CannonballposY = 0;
    TDT4102::Color cannonballColor = TDT4102::Color::transparent;
    
    double targetPosition;

    //GUI
    unsigned int btnWidth = 80;
    unsigned int btnHeight = 30;
    TDT4102::Point shootBtnPoint = {static_cast<int>(w_width - btnWidth), static_cast<int>(btnHeight + 5)};
    TDT4102::Point updateBtnPoint = {static_cast<int>(w_width - btnWidth*2), static_cast<int>(btnHeight + 5)};
    TDT4102::Point velocityInputPoint = {static_cast<int>(w_width - btnWidth*2), static_cast<int>(btnHeight*0)};
    TDT4102::Point thetaInputPoint = {static_cast<int>(w_width - btnWidth), static_cast<int>(btnHeight*0)};
    TDT4102::Point resetBtnPoint = {static_cast<int>(w_width - btnWidth*2), static_cast<int>(btnHeight + 5)*3};


    TDT4102::TextInput thetaDisplay;
    TDT4102::TextInput velocityDisplay;
    TDT4102::Button shootBtn;
    TDT4102::Button updateBtn;
    TDT4102::Button resetBtn;

    //Seiers greier
    std::string victoryText{"U WON!!!"};
    int fontSize{10};
    int textWidth{10};
    int WinXPos{10};
    int WinYPos{10};
    bool gameIsWon = false;
    bool haveCheckedForWin = false;
    TDT4102::Color textColor = TDT4102::Color::white;

    //Kanon
    void drawCannon(double thet, TDT4102::Color fuse);

    TDT4102::Point barrelEnd = {0, 0};
    TDT4102::Point cannonballPos = {0, 0};
    TDT4102::Point boatTargetPoint = {0, w_height};

    int cannonWidth = 30;
    int cannonLength = 100;
    int barrelWidth = 20;
    int wheelRadius = 20;
    double barrelScale = 0.6;

    void drawWindow();
    void drawBoatTarget();
    void drawOcean();
    void drawWin(int i);
    
    void shoot();
    void updateShooting(double timeRatio);
    void resetShooting();

    void changeTheta();
    inline void updateParams();
    double getDistanceTraveled();
    void checkForWin();
    void restart();

    void handleInput();
    void updateDisplay();

public:
    CannonballWindow();
    void run();

    //Hjelpe funksjona
    std::string to_string_with_precision(double value, int precision = 2);

};
