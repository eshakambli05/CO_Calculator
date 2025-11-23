#ifndef COCALCULATOR_H
#define COCALCULATOR_H

#include <utility> // For std::pair

class COCalculator {
public:
    /**
     * @brief Calculates the percentage.
     * @return Percentage (0.0 to 100.0)
     */
    static double calculatePercentage(double obtained, double max);

    /**
     * @brief Determines the attainment level based on percentage.
     * @return Level (0, 1, 2, or 3)
     */
    static int determineLevel(double percentage);

    /**
     * @brief Helper to get both percentage and level in one call.
     * @return std::pair where first is percentage, second is level.
     */
    static std::pair<double, int> calculateMetric(double obtained, double max);
};

#endif // COCALCULATOR_H
