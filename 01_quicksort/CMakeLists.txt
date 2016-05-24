
cmake_minimum_required(VERSION 3.0)

project(SC15_Quicksort CXX)

find_package(HPX REQUIRED)

add_executable(serial_quicksort serial_quicksort.cpp)
hpx_setup_target(serial_quicksort)

add_executable(parallel_quicksort parallel_quicksort.cpp)
hpx_setup_target(parallel_quicksort)
