#include <vector>
#include <algorithm>
#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto isMinimum = [](float const& currMin, float const& next)
{
    return currMin < next;
};

auto isListSorted = [](std::vector<float> const& list)
{
    return std::adjacent_find(list.begin(), list.end(), std::greater<float>()) == list.end();
};

auto sortList = [](std::vector<float> const& list) -> std::vector<float>
{
    if(list.size() <= 1)
        return list;

    std::vector<float> unsorted = list;
    int iteration = 0;

    std::function<void()> sortFunc = [&]()
    {
        int minimumIndex = iteration;

        int index = iteration;
        std::for_each(unsorted.begin() + iteration, unsorted.end(), [&](float const& curr) {
            if(!isMinimum(unsorted[minimumIndex], curr))
            {
                minimumIndex = index;
            }

            index += 1;
        });

        std::swap(unsorted[iteration], unsorted[minimumIndex]);

        iteration += 1;

        if(!isListSorted(unsorted))
        {
            sortFunc();
        }
    };

    sortFunc();
    
    std::vector<float> sorted = unsorted;

    return sorted;
};

TEST_CASE("empty list")
{
    std::vector<float> unsorted = {};

    std::vector<float> expected = {};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("1 element")
{
    std::vector<float> unsorted = {1};

    std::vector<float> expected = {1};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("5 elements")
{
    std::vector<float> unsorted = {14, 36, 9, 93, 80};

    std::vector<float> expected = {9, 14, 36, 80, 93};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("currMin still min")
{
    CHECK(isMinimum(4, 23));
}

TEST_CASE("currMin bigger than other number")
{
    CHECK_FALSE(isMinimum(15, 3));
}

TEST_CASE("list isn't sorted")
{
    std::vector<float> list = {1, 4, 2, 5, 6};

    CHECK_FALSE(isListSorted(list));
}

TEST_CASE("list is sorted")
{
    std::vector<float> list = {1, 2, 3, 4, 5};

    CHECK(isListSorted(list));
}

TEST_CASE("10 elements")
{
    std::vector<float> unsorted = {100, 46, 35, 51, 84, 22, 5, 16, 9, 7};

    std::vector<float> expected = {5, 7, 9, 16, 22, 35, 46, 51, 84, 100};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("15 elements")
{
    std::vector<float> unsorted = {51, 79, 56, 59, 40, 84, 13, 67, 97, 89, 18, 99, 58, 37, 4};

    std::vector<float> expected = {4, 13, 18, 37, 40, 51, 56, 58, 59, 67, 79, 84, 89, 97, 99};

    CHECK_EQ(expected, sortList(unsorted));
}