#include "utilities.h"

double Utilities::randomWithLimits(double lower, double upper) {
    random_device rd;  
    default_random_engine generator(rd()); 
    uniform_real_distribution<double> distribution(lower, upper); 

    return distribution(generator);  
}