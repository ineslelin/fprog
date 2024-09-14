#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int prodWithFunctionalLoops(vector<int> const& numbers)
{
    return accumulate(numbers.begin(), numbers.end(), 1,
                        [](int const a, int const b){ return static_cast<int>(a * b); });
}

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};
    // Calculate and print the product of the vector
    int prod = prodWithFunctionalLoops(numbers);
    cout << "Product of the vector is " << prod << endl;

    return 0;
}

// int main() {
//     vector<int> numbers = {2, 4, 6, 8};
//     // Calculate and print the product of the vector
//     int prod = prodWithFunctionalLoops(numbers);
//     cout << "Product of the vector is " << prod << endl;

//     return 0;
// }

// int main() {
//     vector<int> numbers = {8, 3, 1,};
//     // Calculate and print the product of the vector
//     int prod = prodWithFunctionalLoops(numbers);
//     cout << "Product of the vector is " << prod << endl;

//     return 0;
// }