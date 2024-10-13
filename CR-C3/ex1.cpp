/*
    Example of error management using lambdas, immutable functions, and monads while attempting to read characters from a file.

    Please create a simple program that reads letters from a file and counts them accordingly.

    Please use the "Maybe" monad for error management. The following steps have to be implemented:

    1. First, define the Maybe monad.
    2. Then create a lambda function to read letters from a file.
    3. Next create an immutable function to read letters from the file.
    4. Lastly create a lambda function to count the letters in the file.
    5. Please use a main function to demonstrate the usage.
*/

#include <experimental/optional>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>

template<typename T>
using Maybe = std::experimental::optional<T>;

template<typename T>
Maybe<T> Just(T value) 
{
    return std::experimental::make_optional(value);
}

template<typename T>
Maybe<T> Nothing() 
{
    return std::experimental::nullopt;
}

auto readLettersFromFileLambda = [](std::string const& path) -> std::experimental::optional<std::string>
{
    std::ifstream file(path); 

    std::string line;
    std::vector<std::string> lines;

    if(!file.is_open()) 
        return Nothing<std::string>();
    
    while(getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    std::string contents = std::accumulate(lines.begin(), lines.end(), std::string(),
        [](std::string const& acc, std::string const& curr) {
            return acc.empty() ? curr : acc + '\n' + curr;
        });

    return Just(contents);
};

std::experimental::optional<std::string> readLettersFromFileFunc(std::string const& path)
{
    std::ifstream file(path); 

    std::string line;
    std::vector<std::string> lines;

    if(!file.is_open()) 
        return Nothing<std::string>();
    
    while(getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    std::string contents = std::accumulate(lines.begin(), lines.end(), std::string(),
        [](std::string const& acc, std::string const& curr) {
            return acc.empty() ? curr : acc + '\n' + curr;
        });

    return Just(contents);
}

auto countLetters = [](std::string const& contents) -> std::experimental::optional<int>
{
    int count = 0;

    if(contents.empty())
        return Nothing<int>();

    std::for_each(contents.begin(), contents.end(), [&](char curr){ if(curr != '\n') count += 1; });

    return Just(count);
};

auto printResults = [](std::string const& description, auto const& results)
{
    std::cout << description << ": " << results << std::endl;
};

int main()
{
    auto validResultFromLambda = readLettersFromFileLambda("./txt/valid.txt").value_or("File couldn't be opened");
    printResults("\nCASE 1: Read valid file lambda", validResultFromLambda);

    auto invalidResultFromLambda = readLettersFromFileLambda("./txt/this_is_an_invalid_file.txt").value_or("File couldn't be opened");
    printResults("\nCASE 2: Read invalid file lambda", invalidResultFromLambda);

    auto emptyResultFromLambda = readLettersFromFileLambda("./txt/empty.txt").value_or("File couldn't be opened");
    printResults("\nCASE 3: Read empty file lambda", emptyResultFromLambda);
    
    auto validResultFromFunc = readLettersFromFileFunc("./txt/valid.txt").value_or("File couldn't be opened.");
    printResults("\nCASE 4: Read valid file func", validResultFromFunc);

    auto invalidResultFromFunc = readLettersFromFileFunc("./txt/this_is_an_invalid_file.txt").value_or("File couldn't be opened");
    printResults("\nCASE 5: Read invalid file func", invalidResultFromFunc);

    auto emptyResultFromFunc = readLettersFromFileFunc("./txt/empty.txt").value_or("File couldn't be opened");
    printResults("\nCASE 6: Read empty file func", emptyResultFromFunc);

    auto countResultFromValidStringLambda = countLetters(validResultFromLambda).value_or(0);
    printResults("\nCASE 7: Read valid string lambda", countResultFromValidStringLambda);

    auto countResultFromEmptyStringLambda = countLetters(emptyResultFromLambda).value_or(0);
    printResults("\nCASE 8: Read empty string lambda", countResultFromEmptyStringLambda);

    auto countResultFromValidStringFunc = countLetters(validResultFromFunc).value_or(0);
    printResults("\nCASE 9: Read valid string func", countResultFromValidStringFunc);

    auto countResultFromEmptyStringFunc = countLetters(emptyResultFromFunc).value_or(0);
    printResults("\nCASE 10: Read empty string func", countResultFromEmptyStringFunc);

    return 0;
}