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

template <typename Iter>
void quicksort(Iter left, Iter right)
{
    // Determine the pivot element
    Iter mid = left + (right - left)/2;
    auto && pivot = *mid;

    Iter i = left;
    Iter j = right;

    // Partition our input range
    while(i <= j)
    {
        // Move the right end to the left
        // as long as it's larger than the pivot
        //do
        while (*j > pivot)
            --j;

        // Move the left end to the right
        // as long as it's smaller than the pivot
        while (*i < pivot)
            ++i;

        // If we didn't move too far to the right, swap
        if (i <= j)
        {
            std::swap(*i, *j);
            i++;
            j--;
        }
    }


    // Sort the left half
    if (left < j)
        quicksort(left, j);
    // Sort the right half
    if (i < right)
        quicksort(i, right);
}

int main()
{
    std::vector<int> is{0, 10, 9, 3, 56, 2, 100, 65, 200, 300, 199, 8};

    std::cout << "Before sort: ";
    for(int i: is)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    quicksort(is.begin(), is.end() - 1);
    std::cout << "After sort: ";
    for(int i: is)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
