include(CTest)
project(siglot-functional-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(siglot REQUIRED)
find_package(GTest REQUIRED)
