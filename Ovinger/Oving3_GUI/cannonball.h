#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "std_lib_facilities.h"
#include <iomanip> 
#include <cmath>

class Cannonball{
private:
    double g = -9.81;
    double initPosistionX{0},initPosistionY{0}; 
    double maxError{3};
    //impletere private tall for get her??
public:
    //1.a-e)
    double acclY();
    double velY(double initVelocityY, double time);
    double posX(double initPosistionX, double initVelocityX,double time);
    double posY(double initPosistionY, double initVelocityY,double time);
    double flightTime(double initVelocityY, double y0);
    //4)
    double degToRad(double deg);
    double getVelocityX(double theta, double initVelocity);
    double getVelocityY(double theta, double initVelocity);
};

#endif