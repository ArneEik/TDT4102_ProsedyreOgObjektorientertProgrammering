#include "CannonballWindow.h"
#include "Utilities.h"
#include <chrono>
#include <thread>

CannonballWindow::CannonballWindow()
    : AnimationWindow{30 , 30, w_width, w_height, "Cannon"},
      Cannonball{},
      targetPosition{Utilities::randomWithLimits(static_cast<double>(w_width)/2, static_cast<double>(w_width))},
      shootBtn{shootBtnPoint,btnWidth,btnHeight,"shoot!"},
      updateBtn{updateBtnPoint,btnWidth,btnHeight,"Update"},
      thetaDisplay{thetaInputPoint,btnWidth,btnHeight,"30"},
      velocityDisplay{velocityInputPoint,btnWidth,btnHeight,"80"},
      resetBtn{resetBtnPoint,btnWidth*2,btnHeight,"Reset"}
{
    std::cout<<targetPosition<<endl;
    // Initialiseringskode her
    add(shootBtn);
    add(updateBtn);
    add(thetaDisplay);
    add(velocityDisplay);
    add(resetBtn),

    shootBtn.setCallback(std::bind(&CannonballWindow::shoot, this));
    updateBtn.setCallback(std::bind(&CannonballWindow::updateParams,this));
    resetBtn.setCallback(std::bind(&CannonballWindow::restart, this));
    thetaDisplay.setText(to_string_with_precision(theta_goal));
    velocityDisplay.setText(to_string_with_precision(velocity));
    
    //Bruker tastatur i stede, men gidd ikkje fjerne alt så skyve det under teppe
    shootBtn.setVisible(false);
    updateBtn.setVisible(false);
    thetaDisplay.setVisible(false);
    velocityDisplay.setVisible(false);

    resetBtn.setVisible(false);

    boatTargetPoint.x =static_cast<int>(targetPosition);
    run();
}

void CannonballWindow::run() {
    int iterator{0};
    while(!should_close()) {
        handleInput();
        while (abs(current_theta-theta_goal) >= tol)
        {
            changeTheta();
            drawWindow();
            handleInput();
            next_frame();

        }
        if(isShooting){
            totalTime = flightTime(velY, (w_height - barrelEnd.y));
            totalFrames = static_cast<int>(totalTime * fps); // Totalt antall frames for flygetiden
            for (int frame = 0; frame <= totalFrames; ++frame) {
                double currentTime = frame * frameTime;
                changeTheta();
                drawWindow();
                updateShooting(currentTime / totalTime); // Passerer relativ tid som parameter
                handleInput();
                next_frame();
            }
            cannonballPos.y = w_height;
            missedShots.push_back(cannonballPos);
            resetShooting();
        }
        checkForWin();
        while (gameIsWon) //må få inn ein rest knapp her
        {
            drawWin(iterator);
            ++iterator;
            if(iterator > 400) {
                iterator = 0;
                restart();
            }
            drawWindow();
            next_frame();
        }
        drawWindow();
       
        next_frame();
    }
}

void CannonballWindow::shoot()
{
    updateParams();
    isShooting = true;
}

void CannonballWindow::updateShooting(double timeRatio)
{
    cannonballColor = TDT4102::Color::red;
    CannonballposY = posY(barrelEnd.y, velY, totalTime*timeRatio);
    CannonballposX = posX(barrelEnd.x, velX, totalTime*timeRatio);
    cannonballPos = {static_cast<int>(CannonballposX), static_cast<int>(CannonballposY)};
}

void CannonballWindow::resetShooting()
{
    isShooting = false;
    cannonballColor = TDT4102::Color::transparent;
    haveCheckedForWin = false;
}

void CannonballWindow::changeTheta() {
    static double accumulated_error = 0.0;
    double error = theta_goal - current_theta; // til P-Ledd
    accumulated_error += error; //til I-ledd
    current_theta += error * KP + accumulated_error * KI; // Juster faktorene etter behov
}

void CannonballWindow::updateParams()
{
    updateDisplay();
    theta_goal = stod(thetaDisplay.getText());
    velocity = stod(velocityDisplay.getText());
    velX = velocity*cos(degToRad(theta_goal));
    velY = velocity*sin(degToRad(theta_goal));
}

void CannonballWindow::drawWindow()
{
    //Havet
    drawOcean();
    //baoten
    drawBoatTarget();
    //kanonen
    drawCannon(current_theta, TDT4102::Color::red);
    //Kula
    draw_circle(cannonballPos, 8, cannonballColor);
    //bomma kuler
    for(auto& shot : missedShots){
        draw_circle(shot, 8, TDT4102::Color::black);
    }
    if(gameIsWon){
    //siger
    draw_text({WinXPos, WinYPos}, victoryText, textColor, fontSize, Font::courier_bold_italic);
    }
}

void CannonballWindow::drawCannon(double theta, TDT4102::Color fuse)
{
    // Konverter vinkel til radianer
    double rad = degToRad(theta);

    // Midtpunktet for hjulaksen og heile kanonen
    // TDT4102::Point wheelCenter ={500,500}; //{50, w_height - wheelRadius}; // Fast punkt (hjulaksen)

    // Beregn forskyvningene for rotasjon
    int dxLength = static_cast<int>(cannonLength * cos(rad));
    int dyLength = static_cast<int>(cannonLength * sin(rad));
    int dxWidth = static_cast<int>(cannonWidth * sin(rad));
    int dyWidth = static_cast<int>(cannonWidth * cos(rad));

    // Kanonens kropp
    TDT4102::Point cp0 = {wheelCenter.x, wheelCenter.y}; // nedre venstre (nærmest hjulaksen)
    TDT4102::Point cp1 = {wheelCenter.x - dxWidth, wheelCenter.y - dyWidth}; // øvre venstre
    TDT4102::Point cp3 = {wheelCenter.x + dxLength, wheelCenter.y - dyLength}; // nedre høyre
    TDT4102::Point cp2 = {cp3.x - dxWidth, cp3.y - dyWidth}; // øvre høyre

    // Senterpunktet på enden av kanonens kropp
    TDT4102::Point cannonEndCenter = {(cp2.x + cp3.x) / 2, (cp2.y + cp3.y) / 2};

    // Kanonens løp 
    TDT4102::Point lp0 = {cannonEndCenter.x + (cp3.x-cannonEndCenter.x)/2 , cannonEndCenter.y + (cp3.y-cannonEndCenter.y)/2}; // nedre venstre
    TDT4102::Point lp1 = {cannonEndCenter.x + (cp2.x-cannonEndCenter.x)/2 , cannonEndCenter.y + (cp2.y-cannonEndCenter.y)/2}; // øvre venstre
    TDT4102::Point lp3 = {static_cast<int>(lp0.x + dxLength*barrelScale), static_cast<int>(lp0.y  - dyLength*barrelScale)}; // nedre høyre
    TDT4102::Point lp2 = {static_cast<int>(lp1.x + dxLength*barrelScale), static_cast<int>(lp1.y - dyLength*barrelScale)}; // øvre høyre
    
    // TDT4102::Point cp3 = {wheelCenter.x + dxLength, wheelCenter.y - dyLength}; // nedre høyre
    // TDT4102::Point cp2 = {cp3.x - dxWidth, cp3.y - dyWidth}; // øvre høyre
    // Tegn kroppen av kanonen
    draw_quad(cp0, cp1, cp2, cp3, TDT4102::Color::black);

    // Tegn løpet av kanonen
    draw_quad(lp0, lp1, lp2, lp3, TDT4102::Color::black);

    

    // Tegn avrunding på baken av kanonen
    TDT4102::Point backEnd = {(cp1.x+cp0.x)/2, (cp1.y + cp0.y) / 2};
    draw_circle(backEnd, cannonWidth*2/3, TDT4102::Color::black);

    // Tegn lunte
    TDT4102::Point fuseStart = {backEnd.x, backEnd.y - cannonWidth / 2};
    TDT4102::Point fuseEnd = {fuseStart.x - 10, fuseStart.y - 20}; // Juster lengden og vinkelen på lunta etter behov
    draw_line(fuseStart, fuseEnd, TDT4102::Color::black);
    draw_circle(fuseEnd, 3, fuse);


    // Oppdater barrelEnd for enden av løpet
    barrelEnd = {(lp2.x + lp3.x) / 2, (lp2.y + lp3.y) / 2};
    // draw_circle(barrelEnd, 6, TDT4102::Color::green);
    // Tegn hjul
    draw_circle(wheelCenter, wheelRadius, TDT4102::Color::saddle_brown);
}

void CannonballWindow::drawBoatTarget() {
    // Definer dimensjonane til båten
    int width = 120;
    int height = 30;
    int deckHeight = 10;
    int mastHeight = 60;
    int sailWidth = 40;
    int hullWidth = 10;

    // Definer punkta for båtkroppen (skrog)
    TDT4102::Point leftBottom = {boatTargetPoint.x - width / 2, boatTargetPoint.y};
    TDT4102::Point rightBottom = {boatTargetPoint.x + width / 2, boatTargetPoint.y};
    TDT4102::Point leftTop = {leftBottom.x-10, boatTargetPoint.y - height};
    TDT4102::Point rightTop = {rightBottom.x+20, boatTargetPoint.y - height};

    // Teikn skroget
    draw_quad(leftBottom, rightBottom, rightTop, leftTop, TDT4102::Color::saddle_brown);

    // Definer punkta for dekket
    TDT4102::Point deckLeft = {leftTop.x, leftTop.y - deckHeight};
    TDT4102::Point deckRight = {rightTop.x, rightTop.y - deckHeight};

    // Teikn dekket
    draw_quad(leftTop, rightTop, deckRight, deckLeft, TDT4102::Color::burly_wood);

    // Teikn masta
    TDT4102::Point mastBase = {boatTargetPoint.x, deckLeft.y};
    TDT4102::Point mastTop = {boatTargetPoint.x, deckLeft.y - mastHeight};
    draw_line(mastBase, mastTop, TDT4102::Color::black);

    // Teikn seila
    TDT4102::Point leftSailBottom = {mastBase.x - sailWidth / 2, mastBase.y};
    TDT4102::Point rightSailBottom = {mastBase.x + sailWidth / 2, mastBase.y};
    TDT4102::Point sailTop = {mastTop.x, mastTop.y};

    // Hovudseil
    draw_triangle(sailTop, leftSailBottom, mastBase, TDT4102::Color::khaki);
    draw_triangle(sailTop, rightSailBottom, mastBase, TDT4102::Color::khaki);

    // Teikn baugsprydet
    TDT4102::Point bowspritStart = {rightTop.x, rightTop.y};
    TDT4102::Point bowspritEnd = {rightTop.x + 20, rightTop.y - 10};
    draw_line(bowspritStart, bowspritEnd, TDT4102::Color::black);

    // Teikn vinduene på båten
    int windowHeight = 5;
    int windowWidth = 10;
    int windowSpacing = 5;
    TDT4102::Point window1 = {leftTop.x + 10, leftTop.y + 10};
    TDT4102::Point window2 = {window1.x + windowWidth, window1.y};
    TDT4102::Point window3 = {window2.x, window2.y - windowHeight};
    TDT4102::Point window4 = {window1.x, window1.y - windowHeight};

    draw_quad(window1, window2, window3, window4, TDT4102::Color::cyan);

    window1.x += windowWidth + windowSpacing;
    window2.x += windowWidth + windowSpacing;
    window3.x += windowWidth + windowSpacing;
    window4.x += windowWidth + windowSpacing;

    draw_quad(window1, window2, window3, window4, TDT4102::Color::cyan);

    window1.x += windowWidth + windowSpacing;
    window2.x += windowWidth + windowSpacing;
    window3.x += windowWidth + windowSpacing;
    window4.x += windowWidth + windowSpacing;

    draw_quad(window1, window2, window3, window4, TDT4102::Color::cyan);
}

void CannonballWindow::drawOcean() {
    int landWidth = 200; // Breidde på land
    int skyHeight = 3 * w_height / 4; // Høgde på himmelen (øvre 3/4 av vinduet)
    int sunRadius = 50; // Radius på sola

    // Definer punkta for landet
    TDT4102::Point landTopLeft = {0, skyHeight};
    TDT4102::Point landTopRight = {landWidth, skyHeight};
    TDT4102::Point landBottomLeft = {0, w_height};
    TDT4102::Point landBottomRight = {landWidth, w_height};

    // Teikn land
    draw_quad(landTopLeft, landTopRight, landBottomRight, landBottomLeft, TDT4102::Color::gray);

    // Definer punkta for havet
    TDT4102::Point oceanTopLeft = {landWidth, skyHeight};
    TDT4102::Point oceanTopRight = {w_width, skyHeight};
    TDT4102::Point oceanBottomLeft = {landWidth, w_height};
    TDT4102::Point oceanBottomRight = {w_width, w_height};

    // Teikn hav
    draw_quad(oceanTopLeft, oceanTopRight, oceanBottomRight, oceanBottomLeft, TDT4102::Color::blue);

    // Definer punkta for himmelen
    TDT4102::Point skyTopLeft = {0, 0};
    TDT4102::Point skyTopRight = {w_width, 0};
    TDT4102::Point skyBottomLeft = {0, skyHeight};
    TDT4102::Point skyBottomRight = {w_width, skyHeight};

    // Teikn himmel
    draw_quad(skyTopLeft, skyTopRight, skyBottomRight, skyBottomLeft, TDT4102::Color::light_sky_blue);

    // Teikn sola
    TDT4102::Point sunCenter = {w_width - sunRadius - 80, sunRadius + 20}; // Plassering av sola
    draw_circle(sunCenter, sunRadius, TDT4102::Color::yellow);
}

void CannonballWindow::drawWin(int i)
{
    textColor = TDT4102::Color::red;
    fontSize = 40 + static_cast<int>(15 * sin(i * M_PI / 30));
    textWidth = victoryText.length() * (fontSize / 2);
    WinXPos = (w_width - textWidth) / 2;
    WinYPos = (w_height - fontSize) / 2;
}

double CannonballWindow::getDistanceTraveled(){
    double time = flightTime(velY,(w_height - barrelEnd.y));
    double posXAtGround = posX(barrelEnd.x, velX, time);
    return posXAtGround;    
}

void CannonballWindow::checkForWin()
{
    if(!haveCheckedForWin){    
        gameIsWon = abs(getDistanceTraveled() - targetPosition) <= 8;
        haveCheckedForWin = true;
        gameIsWon == true ? resetBtn.setVisible(true) : resetBtn.setVisible(false);
    }
}

std::string CannonballWindow::to_string_with_precision(double value, int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

void CannonballWindow::restart()
{
    missedShots.clear();
    gameIsWon = false;
    haveCheckedForWin = false;
    textColor = TDT4102::Color::white;
    resetBtn.setVisible(false);
    targetPosition = Utilities::randomWithLimits(static_cast<double>(w_width)/2, static_cast<double>(w_width));
    boatTargetPoint.x = targetPosition;
    // theta_goal += 3630;
}

void CannonballWindow::handleInput() {
    static bool lastUpKeyState = false;
    static bool lastDownKeyState = false;
    static bool lastLeftKeyState = false;
    static bool lastRightKeyState = false;
    static bool lastShiftKeyState = false;
    static bool lastSpaceKeyState = false;
    
    bool currentUpKeyState = is_key_down(KeyboardKey::UP);
    bool currentDownKeyState = is_key_down(KeyboardKey::DOWN);
    bool currentLeftKeyState = is_key_down(KeyboardKey::LEFT);
    bool currentRightKeyState = is_key_down(KeyboardKey::RIGHT);
    bool currentShiftKeyState = is_key_down(KeyboardKey::LEFT_SHIFT);
    bool currentSpaceKeyState = is_key_down(KeyboardKey::SPACE);

    if(currentSpaceKeyState && !lastSpaceKeyState){
        shoot();
    }

    if(currentUpKeyState) {
        std::cout<<"up\n";
        if(currentShiftKeyState){// && !lastUpKeyState) {
            theta_goal += thetaIncrement*10;
        } else if (!currentShiftKeyState){
            theta_goal += thetaIncrement;
            updateParams();
        }
    }

    if(currentDownKeyState) {
        if(currentShiftKeyState){// && !lastDownKeyState) {
            theta_goal -= thetaIncrement*10;
        } else if (!currentShiftKeyState) {
            theta_goal -= thetaIncrement;
            updateParams();
        }
    }

    if(currentRightKeyState) {
        if(currentShiftKeyState){// && !lastRightKeyState) {
            velocity += velocityIncrement*10;
        } else if(!currentShiftKeyState) {
            velocity += velocityIncrement;
            updateParams();
        }
    }

    if(currentLeftKeyState) {
        if(currentShiftKeyState){// && !lastLeftKeyState) {
            velocity -= velocityIncrement*10;
        } else if(!currentShiftKeyState) {
            velocity -= velocityIncrement;
            updateParams();
        }
    }

    lastUpKeyState = currentUpKeyState;
    lastDownKeyState = currentDownKeyState;
    lastLeftKeyState = currentLeftKeyState;
    lastRightKeyState = currentRightKeyState;
    lastShiftKeyState = currentShiftKeyState;
    lastSpaceKeyState = currentSpaceKeyState;

    // Oppdater skjermen etter endringer
    updateParams();
}

void CannonballWindow::updateDisplay() {
    // Oppdater thetaDisplay og velocityDisplay basert på nye verdier
    thetaDisplay.setText(to_string_with_precision(theta_goal));
    velocityDisplay.setText(to_string_with_precision(velocity));
    draw_text({30,30},"Velocity : " + to_string_with_precision(velocity) + "        " +
                        "Angle : " + to_string_with_precision(current_theta), 
                        TDT4102::Color::red);
}

