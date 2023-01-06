include(CTest)
project(siglot-functional-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(siglot REQUIRED)

add_executable(01_API 01_api.cpp)
target_link_libraries(01_API siglot)

enable_testing()
add_test(NAME "01_API" COMMAND 01_API)