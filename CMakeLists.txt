cmake_minimum_required(VERSION 4.1)
project(CS442_assignment_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS442_assignment_4
        Main.cpp
        Main.h
        part_1_to_3.cpp
        part_1_to_3.h
        history.cpp
        history.h)
