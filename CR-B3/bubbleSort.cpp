#include <vector>
#include <functional>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto isValue1Bigger = [](float const& val1, float const& val2)
{
    return val1 > val2;
};

auto isListSorted = [](std::vector<float> const& list)
{
    return std::adjacent_find(list.begin(), list.end(), std::greater<float>()) == list.end();
};

auto sortList = [](std::vector<float> const& list) -> std::vector<float>
{
    std::vector<float> unsortedList = list;

    do
    {
        std::for_each(unsortedList.begin(), unsortedList.end() - 1, [&](float& curr) {
            float& next = *(&curr + 1);

            if(isValue1Bigger(curr, next))
            {
                std::swap(curr, next);
            }
        });
    } while (!isListSorted(unsortedList));
    
    return unsortedList;
};

TEST_CASE("5 elements")
{
    std::vector<float> unsorted = {14, 36, 9, 93, 80};

    std::vector<float> expected = {9, 14, 36, 80, 93};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("val1 is bigger")
{
    CHECK(isValue1Bigger(6, 2));
}

TEST_CASE("val2 is bigger")
{
    CHECK_FALSE(isValue1Bigger(2, 4));
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