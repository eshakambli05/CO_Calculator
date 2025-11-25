#ifndef COCALCULATOR_H
#define COCALCULATOR_H

#include <utility>
#include <vector>

class COCalculator {
public:
    static double calculatePercentage(double obtained, double max);
    static int determineLevel(double percentage);
    static std::pair<double, int> calculateMetric(double obtained, double max);

    // Function to calculate PO attainment from CO attainments and mapping
    static double calculatePOAttainment(const std::vector<double>& coAttainments, const std::vector<int>& mappings);
};

#endif // COCALCULATOR_H

