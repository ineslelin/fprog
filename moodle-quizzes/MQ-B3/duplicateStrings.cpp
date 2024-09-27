#include <iostream>
#include <vector>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
using namespace std;

template<class ForwardIt>
ForwardIt remove_duplicates(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return last;
 
    ForwardIt result = first;
    while (++first != last) {
        if (!(*result == *first) && ++result != first) {
            *result = std::move(*first);
        }
    }
    return ++result;
}

TEST_CASE("Remove duplicates from a string (to edit, results in abab)")
{
    string str = "aabbaaabbbbbb";

    sort(str.begin(), str.end());
    auto res = remove_duplicates(str.begin(), str.end());

    CHECK_EQ("ab",string(str.begin(), res));
}

TEST_CASE("Remove duplicates from a string (runs correctly)")
{
    string str = "aaaaabbbbbb";

    sort(str.begin(), str.end());
    auto res = remove_duplicates(str.begin(), str.end());

    CHECK_EQ("ab",string(str.begin(), res));
}