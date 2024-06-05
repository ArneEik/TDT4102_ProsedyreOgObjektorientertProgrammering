#pragma once
#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "AnimationWindow.h"

// Abstrakt klasse. Arvende konkrete klasser må implementere funksjonen draw()
// som tegner former i vinduet de skal bli vist i.
class Emoji{
public:
    virtual void draw(AnimationWindow&) = 0;
    virtual ~Emoji(){}; //destruktør
};

class Face : public Emoji {
protected:
    Point centre;
    int radius;
    // Beskyttet konstruktør forhindrer direkte instansiering men tillater initialisering av subklasser
    Face(Point c, int r) : centre(c), radius(r) {}
public:
    virtual ~Face(){};
    virtual void draw(AnimationWindow& win) override = 0;
};

class EmptyFace : public Face{
protected:
    Point leftEye;
    Point rightEye;
    int eyeRadius;
    Point leftPupilPosition;
    Point rightPupilPosition;
    //munn greier
    Point mouth;
    int mouthHeight;
    int mouthWidth;
    int startDegree;
    int endDegree;
    

public:
    EmptyFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//SMILE
class SmileFace : public EmptyFace{
protected:

public:
    SmileFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//SAD
class SadFace : public EmptyFace{
protected:

public:
    SadFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//ANGRY
class AngryFace : public SadFace{
protected:
    Point leftBrowStart;
    Point leftBrowEnd;
    Point rightBrowStart;
    Point rightBrowEnd;

public:
    AngryFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
    
};
//Wink
class WinkFace : public SmileFace{
protected:
    Point winkCenter;
public:
    WinkFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//SURPRISEDFACE
class SurprisedFace : public SadFace{
public:
    SurprisedFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//CryFace
class CryFace : public SmileFace{
 protected:
    Point tearTop;
    Point tearLeft;   
    Point tearRight;
    Point tearCentre;
public:
    CryFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//SHAKINGDFACE
class ShakingFace : public SurprisedFace{
public:
    ShakingFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};
//SUNGLASSESFACE
class SunglacessesFace : public AngryFace{
protected:
    Point leftLensCentre;
    Point rightLensCentre;
    int lensWidth;
    int lensHeight; 
public:
    SunglacessesFace(Point c, int r, int eyeR);
    virtual void draw(AnimationWindow& win) override;
};