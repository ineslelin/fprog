#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cmath>

using namespace std;
using namespace std::placeholders;
    
    
auto e_power_x = [](const double x){
    return exp(x);
};

auto nat_log = [](const double x){
    return log(x)/log(2.7182818284);
};

template <class F, class G>
auto compose(F f, G g){
  return [=](auto value){return f(g(value));};
}

// TEST_CASE("Composition"){
// /* your code will be placed here */
//     CHECK_EQ(3, doctest::Approx(log_exp(3)));
// 	CHECK_EQ(3, doctest::Approx(exp_log(3)));
// }

// 	CHECK_EQ(exp_log(5.5), doctest::Approx(log_exp(5.5)));
// }