#include "cannonball.h"
#include "utilities.h"
#include "cannonball_viz.h"

Utilities utilities;

//2.a)
double Cannonball::acclY(){
    return g;
}
//2.b)
double Cannonball::velY(double initVelocityY, double time){

    return initVelocityY + acclY()*time;
}
//2.c)
double Cannonball::posX(double initPosistionX, double initVelocityX, double time){
    return initPosistionX + initVelocityX*time;
}
double Cannonball::posY(double initPositionY, double initVelocityY, double time) {
    return initPositionY + initVelocityY * time + 0.5 * acclY() * pow(time, 2);
}

//2.d)
void Cannonball::printTime(double timeInSeconds) {
    int hours =  int(timeInSeconds) / 3600;
    int minutes = (int(timeInSeconds) % 3600) / 60;
    int seconds = int(timeInSeconds) % 60;
    int milliseconds = int((timeInSeconds - int(timeInSeconds)) * 1000);
    cout<< "toal airtime: "
        << setfill('0') << setw(2) << hours << ":"
        << setfill('0') << setw(2) << minutes << ":"
        << setfill('0') << setw(2) << seconds << "."
        << setfill('0') << setw(3) << milliseconds << endl;
}
//2.e)
double Cannonball::flightTime(double initVelocityY){
    return abs(2.0 * initVelocityY / acclY());
}
//3.a) DET FUNKA:)))))))))

//4.a)
double Cannonball::getUserInputTheta(){
    double theta;
    cout<< "choose yor angel (degrees): "; cin>> theta;
    return theta;
}
double Cannonball::getUserInputInitVelocity(){
    double vel{0};
    cout<<"choose your velocity (m/s): "; cin>> vel;
    return vel;
}
double Cannonball::degToRad(double deg){
    return deg * M_PI / 180.0; 
}
double Cannonball::getVelocityX(double theta, double initVelocity){
    return initVelocity*cos(theta);

}
double Cannonball::getVelocityY(double theta, double initVelocity){
    return initVelocity*sin(theta);
}
//4.b)
double Cannonball::getDistanceTraveled(double velocityX, double velocityY){
    double initPosistionX, _ = getInitialPosition();
    double time = flightTime(velocityY);
    double posXAtGround = posX(initPosistionX, velocityX, time);
    return posXAtGround;    
}
//4.c)
double Cannonball:: targetPractice(double distanceToTarget,double velocityX,double velocityY){
    double distanceTraveld = getDistanceTraveled(velocityX,velocityY);
    double distanceDiffrence = distanceToTarget - distanceTraveld;
    return distanceDiffrence;
}

double Cannonball::getInitialPosition(){
    return initPosistionX, initPosistionY;
}
bool Cannonball::isInRange(double target, double posX){
    double deviation = abs(target - posX);

    if (deviation <= maxError) {
        return true;
    } else {
        return false;
    }
}

void Cannonball::playTargetPractice(){
    double distanceDiffrence, time, velocity, angel;
    double target = utilities.randomWithLimits(100, 1000);
    double initPosistionX, initPosistionY = getInitialPosition();
    cout<<"\n*****************************************************************************************************************"<<endl;
    cout<<"welcome to TagetPractice\nYour task is to hit the target placed a palce between 100 and 1000m from the canon\n\n";
    cout<<"yor tools to do so is to set the canon in your desired angel and chooce your veloicity\n";
    for (int count = 0; count< 10; count++){
        cout<<"\n";
        for (int i=0; i<100; i++){cout<<"_";}
        cout<<"\nyou have "<< 10 - count << " lives left!\n";
        angel = getUserInputTheta();
        velocity = getUserInputInitVelocity();
        distanceDiffrence = targetPractice(target,getVelocityX(degToRad(angel), velocity),getVelocityY(degToRad(angel),velocity));
        cannonBallViz(target,1000,getVelocityX(degToRad(angel),velocity),getVelocityY(degToRad(angel),velocity),100);
        if (isInRange(target, posX(initPosistionX,getVelocityX(degToRad(angel),velocity),flightTime(getVelocityY(degToRad(angel),velocity))))){
            cout<< "congrats, u won!"<<endl;
            break;
        }else if(distanceDiffrence < 0){
            cout<<"you shot "<< abs(distanceDiffrence) <<"m to long"<<endl;
        }else{
            cout<<"you shot "<< abs(distanceDiffrence)<<"m to short"<< endl;
        }
        printTime(flightTime(getVelocityY(degToRad(angel),velocity)));
    }cout<<"the target was placed at "<< target<< "meters away"<<endl;
}
