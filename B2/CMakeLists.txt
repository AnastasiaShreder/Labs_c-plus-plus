cmake_minimum_required(VERSION 3.13)
project(B2)

set(CMAKE_CXX_STANDARD 14)

add_executable(B2
        main.cpp
        task1.cpp
        task2.cpp
        tasks.hpp
        queue-interface.hpp
        queue-implementation.hpp
        functions.cpp
        functions.hpp
        )