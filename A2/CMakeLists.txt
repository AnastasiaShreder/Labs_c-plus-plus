cmake_minimum_required(VERSION 3.13)
project(A2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(A2
        common/base-types.hpp
        common/circle.cpp
        common/circle.hpp
        test-main.cpp
        common/rectangle.cpp
        common/rectangle.hpp
        common/shape.hpp)
find_package(Boost)
if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()