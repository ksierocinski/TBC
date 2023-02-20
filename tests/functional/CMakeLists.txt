include(CTest)
project(siglot-functional-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(siglot REQUIRED)
enable_testing()

set(TEST_NAMES_LIST
        01_api
        02_value_signal)

foreach(test_name ${TEST_NAMES_LIST})
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} siglot)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
