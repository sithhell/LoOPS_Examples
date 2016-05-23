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

// Standard C++ Includes
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

template <typename F>
hpx::future<double> integx(F f, double xmin, double xmax, double dx)
{
    hpx::future<double> sum = hpx::make_ready_future(0.0);
    for(double x = xmin + 0.5 * dx; x < xmax; x += dx)
    {
        sum = hpx::lcos::local::dataflow(
            [](hpx::future<double> ff, hpx::future<double> fsum)
            {
                return fsum.get() + ff.get();
            }
          , f(x)
          , sum
        );
    }
    return sum.then(
        [dx](hpx::future<double> fsum)
        {
            return fsum.get() * dx;
        }
    );
}

template <typename F>
double integxy(F f, double xmin, double xmax, double dx, double ymin, double ymax, double dy)
{
    auto fix = [=](double y)
    {
        auto fx = [f, y](double x)
        {
            return hpx::async(f, x, y);
        };
        return integx(fx, xmin, xmax, dx);
    };
    return integx(fix, ymin, ymax, dy).get();
}

double f(double x, double y)
{
    return std::exp(-(x * x + y * y));
}

int main()
{
    std::cout << integxy(&f, 0, 10, 0.003, 0, 10, 0.003) << "\n";
    return 0;
}
