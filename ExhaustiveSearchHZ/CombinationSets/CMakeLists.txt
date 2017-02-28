cmake_minimum_required(VERSION 3.5)
project(CombinationSets)

# Build dirs ===========================================================
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

# Eigen ================================================================
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Qt ===================================================================
find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})

# Boost ================================================================
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
find_package(Boost COMPONENTS
        REQUIRED system filesystem)

# Main executable ======================================================
set(SOURCE_FILES main.cpp
        src/for_each_permutation.h
        src/utilities.hpp)

# Executable
add_executable(CombinationSets ${SOURCE_FILES})
target_link_libraries(CombinationSets
        Qt5::Core
        ${Boost_LIBRARIES})
set_target_properties(CombinationSets
        PROPERTIES COMPILE_FLAGS "-fPIC")

# Testing: general =====================================================
include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}
        tests)

# Testing: utilities ===================================================
add_executable(test_utilities
        tests/test_utilities.cpp)
target_link_libraries(test_utilities
        Qt5::Core
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES})
set_target_properties(test_utilities
        PROPERTIES COMPILE_FLAGS "-fPIC")

# Testing: combination functions =======================================
add_executable(test_combination_function
        tests/test_combination_function.cpp)
target_link_libraries(test_combination_function
        Qt5::Core
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES})
set_target_properties(test_combination_function
        PROPERTIES COMPILE_FLAGS "-fPIC")

#Note: ${GTEST_BOTH_LIBRARIES} necessary to avoid
#having to introduce main() function for test part