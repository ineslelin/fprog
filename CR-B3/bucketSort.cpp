#include <vector>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

using Bucket = std::vector<float>;

auto findBucketIndex = [](float const& item, int numBuckets, float maxVal) -> int 
{
    if (item < 0) return 0;
    if (item >= maxVal) return numBuckets - 1;
    return static_cast<int>(item / (maxVal / numBuckets));
};

auto sortBucket = [](Bucket const& unsortedBucket) -> Bucket
{
    Bucket sortedBucket;

    std::for_each(unsortedBucket.begin(), unsortedBucket.end(), [&](float const& curr)
    {
        auto pos = std::lower_bound(sortedBucket.begin(), sortedBucket.end(), curr);
        sortedBucket.insert(pos, curr);
    });

    return sortedBucket;
};

auto sortList = [](std::vector<float> const& list) -> std::vector<float>
{
    if(list.size() <= 1)
        return list;

    float maxVal = *std::max_element(list.begin(), list.end());
    int numBuckets = std::max(1, static_cast<int>(list.size() / 2));

    std::vector<Bucket> unsortedBuckets(numBuckets);
    
    std::for_each(list.begin(), list.end(), [&](float const& item) {
        int i = findBucketIndex(item, numBuckets, maxVal);
        unsortedBuckets[i].push_back(item);
    });

    std::vector<Bucket> sortedBuckets;
    std::transform(unsortedBuckets.begin(), unsortedBuckets.end(), std::back_inserter(sortedBuckets),
        [&](Bucket const& unsorted) { return sortBucket(unsorted); }
    );

    std::vector<float> sortedList;
    std::for_each(sortedBuckets.begin(), sortedBuckets.end(), [&](Bucket const& bucket) {
        std::for_each(bucket.begin(), bucket.end(), [&](float const& item) {
            sortedList.push_back(item);
        });
    });

    return sortedList;
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
    std::vector<float> unsorted = {0.12, 0.86, 0.11, 0.38, 0.21};

    std::vector<float> expected = {0.11, 0.12, 0.21, 0.38, 0.86};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("10 elements")
{
    std::vector<float> unsorted = {0.73, 0.09, 0.63, 0.44, 0.32, 0.98, 0.61, 0.68, 0.29, 0.63};

    std::vector<float> expected = {0.09, 0.29, 0.32, 0.44, 0.61, 0.63, 0.63, 0.68, 0.73, 0.98};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("15 elements")
{
    std::vector<float> unsorted = {0.87, 0.4, 0.6, 0.62, 0.09, 0.36, 0.87, 0.16, 0.37, 0.42, 0.52, 0.64, 0.92, 0.34, 0.43};

    std::vector<float> expected = {0.09, 0.16, 0.34, 0.36, 0.37, 0.4, 0.42, 0.43, 0.52, 0.6, 0.62, 0.64, 0.87, 0.87, 0.92};

    CHECK_EQ(expected, sortList(unsorted));
}

TEST_CASE("find bucket index")
{
    CHECK_EQ(3, findBucketIndex(0.324, 10, 1));
}

TEST_CASE("are buckets sorted")
{
    Bucket unsorted = {0.23, 0.25, 0.212, 0.289, 0.20};

    Bucket sorted = {0.20, 0.212, 0.23, 0.25, 0.289};

    CHECK_EQ(sorted, sortBucket(unsorted));
}
