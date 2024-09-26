#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"

double integral(const std::vector<double> &function_points, double d)
{
    return std::accumulate(
        function_points.cbegin(), function_points.cend(),
        0.0,
        [d](double accumulated, double point) {
            return accumulated + (point * d);
        }
    );
}

TEST_CASE ("integral 1")
{
    std::vector<double> values{4, 12, 23, 45};
    CHECK_EQ(84, doctest::Approx(integral(values, 1)));
}

TEST_CASE ("integral 2")
{
    std::vector<double> values{123, 432, 678, 145, 321, 543};
    CHECK_EQ(1121, doctest::Approx(integral(values, 0.5)));
}