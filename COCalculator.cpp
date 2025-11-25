#include "COCalculator.h"
#include <cmath>

// 1. Percentage Calculation
double COCalculator::calculatePercentage(double obtained, double max) {
    if (max <= 0) return 0.0;
    return (obtained / max) * 100.0;
}

// 2. Determine Level (60/50/40 Thresholds)
int COCalculator::determineLevel(double percentage) {
    if (percentage >= 60.0) return 3; // High
    if (percentage >= 50.0) return 2; // Medium
    if (percentage >= 40.0) return 1; // Low
    return 0; // Not Attained
}

// 3. Helper for Metric Pair
std::pair<double, int> COCalculator::calculateMetric(double obtained, double max) {
    double pct = calculatePercentage(obtained, max);
    int lvl = determineLevel(pct);
    return {pct, lvl};
}

// 4. PO / PSO Attainment Calculation (Weighted Average)
double COCalculator::calculatePOAttainment(const std::vector<double>& coAttainments, const std::vector<int>& mappings) {
    double weightedSum = 0.0;
    double totalWeight = 0.0;

    // Safety check
    if (coAttainments.size() != mappings.size()) return 0.0;

    for (size_t i = 0; i < coAttainments.size(); ++i) {
        // Only include COs that have a mapping (value > 0)
        if (mappings[i] > 0) {
            weightedSum += (coAttainments[i] * mappings[i]);
            totalWeight += mappings[i];
        }
    }

    // Prevent division by zero
    if (totalWeight == 0) return 0.0;

    return weightedSum / totalWeight;
}
