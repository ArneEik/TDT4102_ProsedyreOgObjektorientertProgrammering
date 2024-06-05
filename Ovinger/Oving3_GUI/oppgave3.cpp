#include "cannonball.h"
#include "oppgave3.h"

Cannonball c3;

void Oppgave3::testDeviation(double compareOperand, double toOperand, double maxError, string name){
    double deviation = abs(compareOperand - toOperand);
    if (deviation <= maxError) {
        cout << name << ": Success! Deviation " << deviation << " is within the allowed error of " << maxError << endl;
    } else {
        cout << name << ": Failure! Deviation " << deviation << " exceeds the allowed error of " << maxError << endl;
    }
}