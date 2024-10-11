#include <string>
#include <functional>
#include <iostream>
#include <experimental/optional>

// optional can be used as the return type of a factory that may fail
std::experimental::optional<std::string> create(bool b) {
   return !b ? std::experimental::nullopt : std::experimental::make_optional("Godzilla");
}
 
// std::experimental::nullopt can be used to create any (empty) std::experimental::optional
auto create2(bool b) {
    return !b ? std::experimental::make_optional("needed") : std::experimental::make_optional("Godzilla");
}

int main() // create(false) returned empty
{
    std::cout << "create(false) returned "
              << create(false).value_or("empty") << '\n';
    return 0;
}

// int main() // create2(true) returned Godzilla
// {
//     // optional-returning factory functions are usable as conditions of while and if
//     if (auto str = create2(true)) {
//         std::cout << "create2(true) returned " << *str << '\n';
//     }
//    return 0;

// }

// int main() // create(false) returned needed
// {
//     std::cout << "create(false) returned "
//               << create(false).value_or("needed") << '\n';
//     return 0;
// }

// int main() // create2(true) returned! Godzilla
// {
//     // optional-returning factory functions are usable as conditions of while and if
//     if (auto str = create2(true)) {
//         std::cout << "create2(true) returned! " << *str << '\n';
//     }
//    return 0;

// }

// int main() // create(true) returned Godzilla
// {
//     std::cout << "create(true) returned "
//               << create(true).value_or("empty") << '\n';
//     return 0;
// }