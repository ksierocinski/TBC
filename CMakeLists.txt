cmake_minimum_required(VERSION 3.10)
project(TBC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# project options
option(BUILD_SHARED_LIBS        "Build shared library instead of static"    ON)
option(BUILD_EXAMPLES           "Builds examples (C++17 required)"          ON)
option(BUILD_TESTS              "Builds all tests (gtest required)"         ON)
option(BUILD_UNIT_TESTS         "Builds unit tests (gtest required)"        ON)
option(BUILD_FUNCTIONAL_TESTS   "Builds funtional tests"                    ON)

# build the library
include_directories(include/)
set(SRC src/callback.cpp
        src/callbackQueue.cpp
        src/receiverBase.cpp
        src/senderBase.cpp
        src/tbc.cpp
        src/tbcCore.cpp)

add_library(TBC ${SRC})

# build examples
if (${BUILD_EXAMPLES})
     add_subdirectory("examples")
endif()

# build tests
if (${BUILD_TESTS})
    enable_testing()
     
    if (${BUILD_UNIT_TESTS})
         add_subdirectory("tests/unit")
    endif()

    if (${BUILD_FUNCTIONAL_TESTS})
         add_subdirectory("tests/functional")
    endif()
endif()

# create a version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/TBCConfigVersion.cmake"
                                 VERSION 1.0
                                 COMPATIBILITY AnyNewerVersion)

# install commands
install(TARGETS TBC
        EXPORT TBCTargets
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tbc
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/TBCConfig.cmake.in"
                                "${PROJECT_BINARY_DIR}/TBCConfig.cmake"
                                INSTALL_DESTINATION lib/cmake/tbc)

install(EXPORT TBCTargets DESTINATION lib/cmake/tbc)
install(FILES "${PROJECT_BINARY_DIR}/TBCConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/TBCConfig.cmake"
              DESTINATION lib/cmake/tbc)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
