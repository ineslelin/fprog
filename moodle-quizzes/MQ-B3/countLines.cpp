#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
using namespace std;

auto count_lines = [](std::string s) -> int
{
    int count = 0;

    return count;
};

TEST_CASE("Counting newlines in a string 1")
{
    string s = "Hello\nWorld\n";

    CHECK_EQ(2,count_lines(s));
}

TEST_CASE("Counting newlines in a string 2")
{
    string s = "What\na\nbeautifull\nworld\n";

    CHECK_EQ(4,count_lines(s));
}