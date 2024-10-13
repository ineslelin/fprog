/*
    Example to demonstrates error management using lambdas, immutable functions, and monads while attempting to invert a n x n matrix.

    1. First, define a simple matrix and a Result monad. The Result monad will be used to represent the outcome of the matrix inversion operation, either holding the inverted matrix if successful or an error message if not.
    2. Then implement a simple determinant function to help us check if the matrix can be inverted.
    3. With the determinant function in place, you should now create an immutable function that attempts to invert the matrix using a lambda and the Result monad.
    4. Finally, please use the invert_matrix lambda function to invert a sample matrix and handle any errors.
*/

#include <experimental/optional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <eigen3/Eigen/Dense>

template<typename T>
using Result = std::experimental::optional<T>;

template<typename T>
Result<T> Invertible(T value) 
{
    return std::experimental::make_optional(value);
}

template<typename T>
Result<T> Nothing() 
{
    return std::experimental::nullopt;
}

std::experimental::optional<bool> canMatrixBeInverted(Eigen::MatrixXd const& matrix)
{
    if(matrix.rows() != matrix.cols())
        return Nothing<bool>();

    return matrix.determinant() != 0 ? Invertible(true) : Nothing<bool>();
}

auto invertMatrix = [](Eigen::MatrixXd const& matrix) -> std::experimental::optional<Eigen::MatrixXd>
{
    if(!canMatrixBeInverted(matrix).value_or(false))
        return Nothing<Eigen::MatrixXd>();
    
    Eigen::MatrixXd matrixInverse =  matrix.inverse(); // no side effects because inverse() returns a new matrix

    return Invertible(matrixInverse);
};

auto printResults = [](std::string const& description, Eigen::MatrixXd const& results)
{
    std::cout << description << ":\n" << results << std::endl;
};

int main()
{
    Eigen::MatrixXd invertible1(2, 2);
    invertible1 << 2, 7,
                  2, 8;

    printResults("Invertible Matrix before", invertible1);

    auto invertedMatrix1 = invertMatrix(invertible1).value_or(invertible1);
    printResults("Invertible Matrix after", invertedMatrix1);


    Eigen::MatrixXd invertible2(3, 3);
    invertible2 << 0, 1, 2,
                   1, 2, 3,
                   3, 1, 1;

    printResults("Invertible Matrix before", invertible2);

    auto invertedMatrix2 = invertMatrix(invertible2).value_or(invertible2);
    printResults("Invertible Matrix after", invertedMatrix2);


    Eigen::MatrixXd notInvertible1(2, 2);
    notInvertible1 << 2, 4,
                      4, 8;

    printResults("Not Invertible Matrix before", notInvertible1);

    auto notInvertedMatrix1 = invertMatrix(notInvertible1).value_or(notInvertible1);
    printResults("Not Invertible Matrix after", notInvertedMatrix1);


    Eigen::MatrixXd notInvertible2(3, 2);
    notInvertible2 << 2, 4,
                      4, 8,
                      4, 6;

    printResults("Not Invertible Matrix before", notInvertible2);

    auto notInvertedMatrix2 = invertMatrix(notInvertible2).value_or(notInvertible2);
    printResults("Not Invertible Matrix after", notInvertedMatrix2);

    return 0;
}