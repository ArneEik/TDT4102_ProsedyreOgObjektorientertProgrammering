#include "Emoji.h"
//FACE
void Face::draw(AnimationWindow& win) {
    win.draw_circle(centre, radius, Color::yellow); 
}
// EMPTYFACE
EmptyFace::EmptyFace(Point c, int r, int eyeR) : Face(c,r), eyeRadius(eyeR){
    leftEye = {c.x - r/4, c.y - r/4}; 
    rightEye = {c.x + r/4, c.y - r/4}; 
    leftPupilPosition = {leftEye.x, static_cast<int>(leftEye.y + round(eyeRadius * 0.1))};
    rightPupilPosition = {rightEye.x, static_cast<int>(rightEye.y + round(eyeRadius * 0.1))};
    //munn plasering
    mouth = {c.x, static_cast<int>(c.y+c.y*0.1)};
    mouthHeight = r/5;
    mouthWidth = r/3;
    startDegree = 0;
    endDegree = 180;
}
void EmptyFace::draw(AnimationWindow& win){
    Face::draw(win);
    win.draw_circle(leftEye, eyeRadius, Color::white);
    win.draw_circle(rightEye,eyeRadius, Color::white);
    win.draw_circle(leftPupilPosition, eyeRadius * 0.2, Color::black);
    win.draw_circle(rightPupilPosition, eyeRadius * 0.2, Color::black);
}
//SMILIYFACE
SmileFace::SmileFace(Point c, int r, int eyeR) : EmptyFace(c, r, eyeR){
}
void SmileFace::draw(AnimationWindow& win){
     Face::draw(win);
     EmptyFace::draw(win);
     win.draw_arc(mouth, mouthWidth, -mouthHeight, startDegree, endDegree, Color::black);
}
//SADFACE
SadFace::SadFace(Point c, int r, int eyeR) : EmptyFace(c, r, eyeR){
}
void SadFace::draw(AnimationWindow& win){
    Face::draw(win);
    EmptyFace::draw(win);
    win.draw_arc(mouth, mouthWidth, mouthHeight, startDegree, endDegree, Color::black);
} 
//ANGRYFACEvoid TDT4102::AnimationWindow::draw_line(TDT4102::Point start, TDT4102::Point end, TDT4102::Color color = TDT4102::Color::black)
AngryFace::AngryFace(Point c, int r, int eyeR) : SadFace(c, r, eyeR){
    rightBrowStart = {rightEye.x+10,rightEye.y -30};
    rightBrowEnd = {rightEye.x-10,rightEye.y -20};
    leftBrowStart = {leftEye.x-10,leftEye.y -30};
    leftBrowEnd = {leftEye.x+10,leftEye.y -20};
}
void AngryFace::draw(AnimationWindow& win){
    Face::draw(win);
    EmptyFace::draw(win);
    SadFace::draw(win);
    win.draw_line(rightBrowStart, rightBrowEnd, Color::brown);
    win.draw_line(leftBrowStart, leftBrowEnd, Color::brown);
}
//WINKFACE
WinkFace::WinkFace(Point c, int r, int eyeR) : SmileFace(c, r, eyeR){
    winkCenter = {rightEye.x,rightEye.y+5};
}
void WinkFace::draw(AnimationWindow& win){
    Face::draw(win);
    EmptyFace::draw(win);
    SmileFace::draw(win);
    win.draw_circle(rightEye,eyeRadius, Color::yellow);
    win.draw_arc(winkCenter, eyeRadius, eyeRadius/2, startDegree, endDegree, Color::black);
}
//SURPRISEFACE
SurprisedFace::SurprisedFace(Point c, int r, int eyeR) : SadFace(c, r, eyeR){
}
void SurprisedFace::draw(AnimationWindow& win){
    Face::draw(win);
    EmptyFace::draw(win);
    SadFace::draw(win);
    win.draw_arc(mouth, mouthWidth, -mouthHeight, startDegree, endDegree, Color::black);
}
//CRYFACE
CryFace::CryFace(Point c, int r, int eyeR) : SmileFace(c, r, eyeR){
    tearTop = {leftEye.x -9, leftEye.y +r/8};
    tearLeft = {tearTop.x-5,tearTop.y+20};
    tearRight = {tearTop.x+5,tearTop.y+20};
    tearCentre = {tearTop.x,tearTop.y+20};
}
void CryFace::draw(AnimationWindow& win) {
    Face::draw(win);
    EmptyFace::draw(win);
    SmileFace::draw(win);
    win.draw_triangle(tearLeft,tearTop,tearRight,Color::blue);
    win.draw_circle(tearCentre, 5, Color::blue);
}
//SHAKINGFACE
ShakingFace::ShakingFace(Point c, int r, int eyeR) : SurprisedFace(c, r, eyeR) {}

void ShakingFace::draw(AnimationWindow& win) {
    win.draw_circle({centre.x-radius*3/5,centre.y}, radius*1.1, Color::beige); 
    win.draw_circle({centre.x+radius*3/5,centre.y}, radius*1.1, Color::beige); 
    SurprisedFace::draw(win);
}
//SUNGLASSESFACE
SunglacessesFace::SunglacessesFace(Point c, int r, int eyeR) : AngryFace(c, r, eyeR){
    leftLensCentre = leftEye;
    rightLensCentre = rightEye;
    lensWidth = eyeRadius * 2; 
    lensHeight = eyeRadius; 
}
void SunglacessesFace::draw(AnimationWindow& win){
    Color sunglassesColor = Color::black;
    AngryFace::draw(win);
    win.draw_circle(leftLensCentre, lensWidth / 2, sunglassesColor);
    win.draw_circle(rightLensCentre, lensWidth / 2, sunglassesColor);

    Point bridgeStart = {leftLensCentre.x + lensWidth / 2, leftLensCentre.y};
    Point bridgeEnd = {rightLensCentre.x - lensWidth / 2, rightLensCentre.y};
    win.draw_line(bridgeStart, bridgeEnd, sunglassesColor);

    Point leftStemStart = {leftLensCentre.x - lensWidth / 2, leftLensCentre.y-5};
    Point leftStemEnd = {leftStemStart.x - lensWidth , leftStemStart.y - lensHeight};
    win.draw_line(leftStemStart, leftStemEnd, sunglassesColor);

    Point rightStemStart = {rightLensCentre.x + lensWidth / 2, rightLensCentre.y-5};
    Point rightStemEnd = {rightStemStart.x + lensWidth , rightStemStart.y - lensHeight} ;
    win.draw_line(rightStemStart, rightStemEnd, sunglassesColor);
}
