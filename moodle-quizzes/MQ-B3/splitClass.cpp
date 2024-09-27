#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
#include <cmath>

using namespace std;

// split the class into pure functions

class Rectangle {
    float width=0.0, height=0.0;
  public:
    Rectangle(float x, float y) : width(x), height(y) {}
    float area() {return abs(width*height);}
    int circumfence() {return abs(2*(width+height));}
    float diagonal() {return sqrt(pow(width,2)+pow(height,2));}
}; 

auto initialize = [] (const auto width, const auto height) -> std::map<string, function<float()>>{
return {
	{"area", bind(area, width, height)},
	{"circumference", bind(circumference, width, height)},
	{"diagonal", bind(diagonal, width, height)}
	};
};



TEST_CASE ("Rectangle 1")
{
  Rectangle rect(3,4);
  CHECK_EQ (12, rect.area());
  CHECK_EQ (14, rect.circumfence());
  CHECK_EQ (5, rect.diagonal());
} 

TEST_CASE ("Rectangle 2")
{
  auto rectangle = initialize(3, 4);
  CHECK_EQ(12, doctest::Approx(rectangle["area"]()));
  CHECK_EQ(14, doctest::Approx(rectangle["circumference"]()));
  CHECK_EQ(5, doctest::Approx(rectangle["diagonal"]()));
  
}

TEST_CASE ("Rectangle 3")
{
  auto rectangle = initialize(3.5, 4.5);
  CHECK_EQ(15.75, doctest::Approx(rectangle["area"]()));
  CHECK_EQ(16.0, doctest::Approx(rectangle["circumference"]()));
  CHECK_EQ(5.70088, doctest::Approx(rectangle["diagonal"]()));
}