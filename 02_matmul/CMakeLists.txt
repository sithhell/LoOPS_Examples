
cmake_minimum_required(VERSION 3.0)

project(SC15_Matmul CXX)

find_package(HPX REQUIRED)

add_executable(serial_matmul serial_matmul.cpp)
hpx_setup_target(serial_matmul)

add_executable(parallel_matmul parallel_matmul.cpp)
hpx_setup_target(parallel_matmul)
