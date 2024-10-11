/*
    Example to demonstrates error management using lambdas, immutable functions, and monads while attempting to invert a n x n matrix.

    1. First, define a simple matrix and a Result monad. The Result monad will be used to represent the outcome of the matrix inversion operation, either holding the inverted matrix if successful or an error message if not.
    2. Then implement a simple determinant function to help us check if the matrix can be inverted.
    3. With the determinant function in place, you should now create an immutable function that attempts to invert the matrix using a lambda and the Result monad.
    4. Finally, please use the invert_matrix lambda function to invert a sample matrix and handle any errors.
*/