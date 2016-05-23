///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

// Standard C++ Includes
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

template <typename F>
double integx(F f, double xmin, double xmax, double dx)
{
    double sum = 0;
    for(double x = xmin + 0.5 * dx; x < xmax; x += dx)
    {
        sum += f(x);
    }
    return sum * dx;
}

template <typename F>
double integxy(F f, double xmin, double xmax, double dx, double ymin, double ymax, double dy)
{
    auto fix = [=](double y)
    {
        auto fx = [f, y](double x)
        {
            return f(x, y);
        };
        return integx(fx, xmin, xmax, dx);
    };
    return integx(fix, ymin, ymax, dy);
}

double f(double x, double y)
{
    return std::exp(-(x * x + y * y));
}

int main()
{
    std::cout << integxy(&f, 0., 10., 0.003, 0., 10., 0.003) << "\n";
}
