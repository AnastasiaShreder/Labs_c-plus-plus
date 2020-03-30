cmake_minimum_required(VERSION 3.13)
project(A4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(A4
        base-types.hpp
        circle.cpp
        circle.hpp
        main.cpp
        composite-shape.hpp
        composite-shape.cpp
        rectangle.cpp
        rectangle.hpp
        shape.hpp
        triangle.hpp
        triangle.cpp
        matrix.hpp
        stratification.cpp
        stratification.hpp
        )
find_package(Boost)
if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()