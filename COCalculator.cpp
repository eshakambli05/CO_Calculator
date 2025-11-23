#include "COCalculator.h"

double COCalculator::calculatePercentage(double obtained, double max) {
    if (max <= 0) return 0.0;
    return (obtained / max) * 100.0;
}

int COCalculator::determineLevel(double percentage) {
    if (percentage >= 60.0) return 3; // Changed from 70 to 60
    if (percentage >= 50.0) return 2; // Changed from 60 to 50
    if (percentage >= 40.0) return 1; // Changed from 50 to 40
    return 0; // Below 40%
}

std::pair<double, int> COCalculator::calculateMetric(double obtained, double max) {
    double pct = calculatePercentage(obtained, max);
    int lvl = determineLevel(pct);
    return {pct, lvl};
}
