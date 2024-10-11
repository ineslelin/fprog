/*
    Example demonstrating error management using lambdas, immutable functions, and monads while solving the cubic equation. You'll have to use the std::optional monad to handle cases where the solution is complex or the equation is not quadratic.

    1. First, create a simple cubic_Solution struct to represent the solutions.
    2. Then implement the solve_cubic lambda function, which takes the coefficients a, b, c and d and returns an std::optional<cubic_Solution>.
    3. Finally, use the solve_cubic lambda function to solve the cubiic equation and handle any errors.
*/