cmake_minimum_required(VERSION 3.22)
project(GLIB)

# Set compiler flags for C++ with optimization level -O3
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_STANDARD 20)

# Find OpenMP library
find_package(OpenMP)
if(OPENMP_FOUND)
    # If OpenMP is found, add OpenMP flags for C and C++ with optimization level -O3
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O3")
    # Set linker flags for OpenMP
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Fetch and include the argparse library from GitHub repository
include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Enable FetchContent module for Google Test
FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0  # Choose an appropriate version
)
FetchContent_MakeAvailable(gtest)

# Set directories for includes and source files
set(GLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GLIB_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Add include directories
include_directories(${GLIB_INCLUDE_DIR})
include_directories(${GLIB_SRC_DIR})
include_directories(${GLIB_TEST_DIR})

# Add subdirectory for source files
add_subdirectory(${GLIB_SRC_DIR})

# Create the main executable
add_executable(GLIB main.cpp)

# Link the argparse and src libraries to the main executable
target_link_libraries(GLIB PRIVATE src argparse)

# Create the test executable
add_executable(test_graph ${GLIB_TEST_DIR}/test_graph.cpp)

# Link Google Test, GMock, and Graph library to the test executable
target_link_libraries(test_graph gtest gtest_main gmock src)

# Enable testing and add the test
enable_testing()
add_test(NAME MyTest COMMAND test_graph)

# Set the default build type to Release if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
