///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:488)
#pragma warning(disable:858)

#include <hpx/hpx_main.hpp>

#include <hpx/hpx.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/include/iostreams.hpp>

void hello_locality()
{
    // Get the ID of the locality this function is executed on
    std::size_t id = hpx::get_locality_id();

    // Print a message using hpx::cout (sends the output to locality 0)
    hpx::cout
        << "Hello, I am executed on Locality " << id << std::endl;

    using hpx::parallel::for_each;
    using hpx::parallel::par;
    using hpx::parallel::static_chunk_size;

    // An integer range being used in a parallel loop
    auto range = boost::irange<std::size_t>(0, hpx::get_os_thread_count());

    // Iterate over the begin of the range until the end in parallel
    for_each(par.with(static_chunk_size())
      , boost::begin(range), boost::end(range)
        // For each element in the range, call the following lambda (anonymous function)
      , [id](std::size_t num_thread)
        {
            // Print a message using hpx::cout (sends the output to locality 0)
            hpx::cout
              << "Hello, I am HPX Thread " << num_thread
              << " executed on Locality " << id << std::endl;
        }
    );
}

// Create hello_locality_action from the hello_locality function
HPX_PLAIN_ACTION(hello_locality)

// Main entry point
int main()
{
    // Get a list of all localities
    auto localities = hpx::find_all_localities();

    // Serially iterate over all localities
    for(auto && locality : localities)
    {
        // Fire & Forget (apply) the hello_locality_action on
        // all localities
        hpx::apply(
            hello_locality_action()
          , locality
        );
    }

    return 0;
}
