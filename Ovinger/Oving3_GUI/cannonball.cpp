#include "cannonball.h"
#include "utilities.h"

Utilities utilities;

//2.a)
double Cannonball::acclY(){
    return g;
}
//2.b)
double Cannonball::velY(double initVelocityY, double time){

    return initVelocityY + acclY()*time;
}

//2.e)
double Cannonball::flightTime(double initVelocityY, double y0) {
    double discriminant = initVelocityY * initVelocityY - 2 * acclY() * y0;
    if (discriminant < 0) {
        return nan(""); // Returner NaN hvis diskriminanten er negativ
    }
    double flightTime = (initVelocityY + sqrt(discriminant)) / acclY();
    std::cout<<flightTime<<std::endl;
    return abs(flightTime);
}

double Cannonball::posY(double initPosY, double initVelocityY, double time) {
    double yPos = initPosY - initVelocityY * time - 0.5 * acclY() * time * time;
    // std::cout<<"initial velY " << initVelocityY << "posY: " << yPos << std::endl;
    return yPos;
}

double Cannonball::posX(double initPosX, double initVelocityX, double time) {
    double xPos = initPosX + initVelocityX * time;
    // std::cout << "posX: " << xPos << std::endl;
    return xPos;
}


//4.a)
double Cannonball::degToRad(double deg){
    return deg * M_PI / 180.0; 
}
double Cannonball::getVelocityX(double theta, double initVelocity){
    return initVelocity*cos(theta);

}
double Cannonball::getVelocityY(double theta, double initVelocity){
    return initVelocity*sin(theta);
}
