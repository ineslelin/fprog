#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"

using namespace std;
using namespace std::placeholders;

auto findInCollection = [](const auto& collection, auto lambda){
    auto result = find_if(collection.begin(), collection.end(), lambda);
    return (result == collection.end()) ? std::nullopt : std::optional(*result);
};

auto isprime = [](int const& num) -> bool {
    if(num <= 1)
        return false;

    if(num == 2)
        return true;

    if(num % 2 == 0)
        return false;

    for(int i = 3; i * i <= num; i += 2)
    {
        if(num % i == 0)
            return false;
    }

    return true;
};

TEST_CASE("find in collection 1"){
    vector<int> values{4, 12, 23, 45};

    auto result23 = findInCollection(values, isprime);
    CHECK_EQ(result23, 23);
};

TEST_CASE("find in collection 2"){
    vector<int> values{10, 1, 24, 45};

    auto resultNotFound = findInCollection(values, isprime);
    CHECK(!resultNotFound.has_value());
};

TEST_CASE("find in collection 3"){
    vector<int> values{0, 12, 24, 45};

    auto resultNotFound = findInCollection(values, isprime);
    CHECK(!resultNotFound.has_value());
};