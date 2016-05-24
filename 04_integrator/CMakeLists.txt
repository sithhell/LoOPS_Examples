
cmake_minimum_required(VERSION 3.0)

project(SC15_Integrator CXX)

find_package(HPX REQUIRED)

add_executable(serial_integrator serial_integrator.cpp)
hpx_setup_target(serial_integrator)

add_executable(parallel_integrator parallel_integrator.cpp)
hpx_setup_target(parallel_integrator)
