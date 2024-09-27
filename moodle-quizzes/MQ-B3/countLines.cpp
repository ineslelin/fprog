#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
using namespace std;

auto count_lines = [](std::string s) -> int
{
    int counter = 0;

    auto count = [&](char const c){
        if(c == '\n')
            counter += 1;

        return;
    };

    std::for_each(s.begin(), s.end(), count);

    return counter;
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