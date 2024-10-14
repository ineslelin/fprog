// UNFINISHED

/*
    Example program that performs an n x n matrix division (left division) using the Maybe monad for error management. We'll create a lambda function to handle the division and use the Maybe monad to handle potential errors.
    1. First, define the Maybe monad.
    2. Then create a lambda function for the matrix division operation.
    3. After this create a lambda function to print the result of the division.
    4. Finally, demonstrate the usage in the main function
*/

#include <experimental/optional>
#include <iostream>
#include <algorithm>
#include <vector>
#include<eigen3/Eigen/Dense>

// using Matrix = std::vector<std::vector<int>>;

template <typename T>
using Maybe = std::experimental::optional<T>;

template <typename T>
Maybe<T> Division(T value)
{
    return std::experimental::make_optional(value);
}

template <typename T>
Maybe<T> Nothing()
{
    return std::experimental::nullopt;
}

auto InvertMatrix = [](Eigen::MatrixXd const& matrix) -> std::experimental::optional<Eigen::MatrixXd>
{
    if(matrix.rows() != matrix.cols())
        return Nothing<Eigen::MatrixXd>();

    if(matrix.determinant() == 0)
        return Nothing<Eigen::MatrixXd>();

    auto invertedMatrix = matrix.inverse();

    Eigen::MatrixXd returnMatrix = invertedMatrix;

    return std::experimental::make_optional(returnMatrix);
};

auto MatrixDivision = [](Eigen::MatrixXd const& matrix) -> std::experimental::optional<Eigen::MatrixXd>
{

};

auto printResults = [](std::string const& description, Eigen::MatrixXd const& matrix)
{
    std::cout << description << ":\n" << matrix << std::endl;
};

int main()
{
    Eigen::MatrixXd matrix(3, 3);
    matrix << 0, 1, 2,
              1, 2, 3,
              3, 1, 1;

    printResults("Before division", matrix);

    Eigen::MatrixXd divisionResult = MatrixDivision(matrix);
    printResults("After division", divisionResult);

    return 0;
}