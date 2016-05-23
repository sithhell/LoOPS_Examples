///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:488)
#pragma warning(disable:858)

// HPX Includes
#include <hpx/hpx_main.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_algorithm.hpp>

// Standard C++ Includes
#include <iostream>
#include <vector>

int main()
{
    std::size_t t_end = 100;
    // Initialize our state
    std::size_t N = 10;
    typedef std::vector<double> state_type;
    state_type U[] = {
        state_type(N)
      , state_type(N)
    };

    // Fill with initial values ...
    U[0][0] = 1.0;
    U[0][N-1] = 1.0;

    // Compute the stencil for t_end iterations
    std::size_t idx_old = 0;
    std::size_t idx_new = 1;
    for (std::size_t t = 0; t != t_end; ++t)
    {
        using hpx::parallel::for_each;
        using hpx::parallel::par;

        auto range = boost::irange<std::size_t>(1, N-1);
        for_each(par, boost::begin(range), boost::end(range),
            [&](std::size_t x)
            {
                U[idx_new][x]
                    = U[idx_old][x] + 0.25 * (U[idx_old][x - 1] + 2 * U[idx_old][x] + U[idx_old][x+1]);
            }
        );
        std::swap(idx_old, idx_new);
    }

    std::cout << "Result:\n";
    for(double y : U[idx_old])
    {
        std::cout << y << '\n';
    }

    return 0;
}
