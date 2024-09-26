#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
#include <cmath>

using namespace std;
using namespace std::placeholders;
    
    
auto sin_x = [](const double x){
    return sin(x);
};

auto arc_sin = [](const double x){
    return asin(x);
};

template <class F, class G>
auto compose(F f, G g){
  return [=](auto value){return f(g(value));};
}

TEST_CASE("Composition"){
  auto asin_sin = compose(arc_sin, sin_x);
  auto sin_asin = compose(sin_x, arc_sin);

	CHECK_EQ(0.3, doctest::Approx(asin_sin(0.3)));
	CHECK_EQ(0.3, doctest::Approx(sin_asin(0.3)));
}

// 	CHECK_EQ(0.5, doctest::Approx(asin_sin(0.5)));
// 	CHECK_EQ(0.5, doctest::Approx(sin_asin(0.5)));
// }