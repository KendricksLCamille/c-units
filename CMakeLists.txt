cmake_minimum_required(VERSION 3.27)
project(c_units C)

set(CMAKE_C_STANDARD 23)

add_executable(c_units main.c
        units.c)
