cmake_minimum_required(VERSION 3.10)
project(TBC-benchmarks LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wunused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_subdirectory(00_latency)
add_subdirectory(01_rvalue_to_const)
add_subdirectory(02_const_to_const)
add_subdirectory(03_const_to_value)
add_subdirectory(04_rvalue_to_value)
add_subdirectory(05_const_to_const_1_to_4)
add_subdirectory(06_const_to_value_1_to_4)
add_subdirectory(07_rvalue_to_value_1_to_4)

configure_file(run_all.sh run_all.sh)