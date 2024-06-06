#include "Utilities.h"

double Utilities::randomWithLimits(double lower, double upper) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(lower, upper);

    return distribution(generator);
}
