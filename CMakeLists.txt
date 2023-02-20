cmake_minimum_required(VERSION 3.12)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(
    the_binary
    # src/common/time_point.h
    # src/math/euclidean_distance.h
    # src/math/speed_difference.h
    # src/math/length_difference.h
    # src/utils/parser.h
    src/main.cpp
)

target_include_directories(the_binary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)