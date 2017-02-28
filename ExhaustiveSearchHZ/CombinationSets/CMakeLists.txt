cmake_minimum_required(VERSION 3.6)
project(CombinationSets)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
find_package(Boost COMPONENTS
        REQUIRED system filesystem)

set(SOURCE_FILES main.cpp src/for_each_permutation.h)
add_executable(CombinationSets ${SOURCE_FILES})
target_link_libraries(CombinationSets
        Qt5::Core
        ${Boost_LIBRARIES})

set_target_properties(CombinationSets
        PROPERTIES COMPILE_FLAGS "-fPIC")