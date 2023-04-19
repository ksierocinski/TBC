include(CTest)
project(TBC-functional-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# find_package(TBC REQUIRED)
enable_testing()

set(TEST_NAMES_LIST
        01_api
        02_value_signal
        03_destroy_slot
        04_message_order
        05_message_1_to_N
        06_message_N_to_1
        07_message_N_to_M
        08_run_in_new_thread
        09_force_quit_thread)

foreach(test_name ${TEST_NAMES_LIST})
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} TBC)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
