#include <vector>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto isBiggerThanPivot = [](float const& pivot, float const& number)
{
    return number > pivot;
};

auto sortPartition = [](std::vector<float> const& unsortedPartition) -> std::vector<float>
{
    if(unsortedPartition.size() <= 1)
        return unsortedPartition;

    std::vector<float> sortedPartition;

    std::for_each(unsortedPartition.begin(), unsortedPartition.end(), [&](float const& curr)
    {
        auto pos = std::lower_bound(sortedPartition.begin(), sortedPartition.end(), curr);
        sortedPartition.insert(pos, curr);
    });

    return sortedPartition;
};

auto sortList = [](std::vector<float> const& list) -> std::vector<float>
{
    if(list.size() <= 1)
        return list;

    std::vector<float> unsorted = list;
    float pivot = *unsorted.begin();

    std::vector<float> left;
    std::vector<float> right;

    std::for_each(unsorted.begin() + 1, unsorted.end(), [&](float const& curr)
    {
        if(isBiggerThanPivot(pivot, curr))
        {
            right.push_back(curr);
        }
        else
        {
            left.push_back(curr);
        }
    });

    std::vector<float> sortedLeft = sortPartition(left);
    std::vector<float> sortedRight = sortPartition(right);

    std::vector<float> sorted;
    std::for_each(sortedLeft.begin(), sortedLeft.end(), [&](float const& curr){
        sorted.push_back(curr);
    });

    sorted.push_back(pivot);

    std::for_each(sortedRight.begin(), sortedRight.end(), [&](float const& curr){
        sorted.push_back(curr);
    });

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

TEST_CASE("bigger than pivot")
{
    CHECK(isBiggerThanPivot(56, 58));
}

TEST_CASE("bigger than pivot")
{
    CHECK_FALSE(isBiggerThanPivot(56, 5));
}

TEST_CASE("empty partition")
{
    std::vector<float> unsorted = {};

    std::vector<float> expected = {};

    CHECK_EQ(expected, sortPartition(unsorted));
}

TEST_CASE("1 element in partition")
{
    std::vector<float> unsorted = {1};

    std::vector<float> expected = {1};

    CHECK_EQ(expected, sortPartition(unsorted));
}

TEST_CASE("is partition sorted")
{
    std::vector<float> unsorted = {1, 4, 2, 7};

    std::vector<float> expected = {1, 2, 4, 7};

    CHECK_EQ(expected, sortPartition(unsorted));
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