///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

// Standard C++ Includes
#include <iostream>
#include <iterator>
#include <vector>

// An example implementation of a quadratic Matrix
template <typename T>
struct matrix
{
    explicit matrix(std::size_t N)
      : data_(N * N, 0)
      , N_(N)
    {}

    // Access element on row i and column j
    // non-const: the element of the matrix can be changed
    T & operator()(std::size_t i, std::size_t j)
    {
        return data_[(i * N_) + j];
    }

    // Access element on row i and column j
    // const: the element of the matrix is read only
    T const & operator()(std::size_t i, std::size_t j) const
    {
        return data_[(i * N_) + j];
    }

    // Return the number of rows/columns
    std::size_t size() const
    {
        return N_;
    }

    // Perform the Matrix-Matrix Multiplication:
    friend matrix operator*(matrix const& lhs, matrix const& rhs)
    {
        std::size_t N = lhs.N_;
        // Create the result matrix
        matrix res(N);

        // Iterate over the number of rows
        for(std::size_t i = 0; i < N; ++i)
        {
            // Iterate over the number of columns
            for (std::size_t j = 0; j < N; ++j)
            {
                T r = T(0);
                // Perform the scalar product of the row and column vector
                for(std::size_t k = 0; k < N; ++k)
                {
                    r += lhs(i, k)  * rhs(k, j);
                }
                res(i, j) += r;
            }
        }

        return res;
    }

private:
    std::vector<T> data_;
    std::size_t N_;
};

int main()
{
    std::size_t N = 10;
    // Create Matrix A
    matrix<double> A(N);
    // Create Matrix B
    matrix<double> B(N);

    // Initialize matrices
    // Iterate over the number of rows
    for(std::size_t i = 0; i < N; ++i)
    {
        // Iterate over the number of columns
        for (std::size_t j = 0; j < N; ++j)
        {
            A(i, j) = i + j;
            B(i, j) = i * j;
        }
    }

    // Create Matrix C = A * B
    matrix<double> C = A * B;

    std::cout << "Result:\n";
    // Iterate over the number of rows
    for(std::size_t i = 0; i < N; ++i)
    {
        // Iterate over the number of columns
        for (std::size_t j = 0; j < N; ++j)
        {
            std::cout << C(i, j) << " ";
        }
        std::cout << "\n";
    }
}
