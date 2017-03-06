cmake_minimum_required(VERSION 3.2)
project(ComplementSets LANGUAGES CXX)

# Build dirs ===========================================================
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(BUILD_ON_MAUR_EXP "" OFF)

# Eigen ================================================================
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

# Boost ================================================================
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
find_package(Boost COMPONENTS
        REQUIRED system filesystem)

# Qt ===================================================================
find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})

# Main executable ======================================================
set(SOURCE_FILES main.cpp
        ../CombinationSets/src/utilities.hpp
        src/combination_set.h)

# Executable
add_executable(ComplementSets ${SOURCE_FILES})
target_link_libraries(ComplementSets
        Qt5::Core
        ${Boost_LIBRARIES})
set_target_properties(ComplementSets
        PROPERTIES COMPILE_FLAGS "-fPIC")

# Testing: general =====================================================
include(CTest)
enable_testing()

if(NOT BUILD_ON_MAUR_EXP)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    include_directories(/home/bellout/include/gtest)
endif()

include_directories(tests)

# Testing: utilities ===================================================
add_executable(test_ComplementSets
        tests/test_complement_sets.cpp)

if(NOT BUILD_ON_MAUR_EXP)
    target_link_libraries(test_ComplementSets
            Qt5::Core
            ${GTEST_BOTH_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT}
            ${Boost_LIBRARIES})
else()
    target_link_libraries(test_ComplementSets
            Qt5::Core
            /home/bellout/lib/libgtest_main.a
            /home/bellout/lib/libgtest.a
            ${CMAKE_THREAD_LIBS_INIT}
            ${Boost_LIBRARIES})
endif()
