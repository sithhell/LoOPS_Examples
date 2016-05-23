
cmake_minimum_required(VERSION 3.0)

project(SC15_Stencil CXX)

find_package(HPX REQUIRED)

add_executable(serial_stencil serial_stencil.cpp)

add_executable(parallel_stencil parallel_stencil.cpp)
hpx_setup_target(parallel_stencil)
