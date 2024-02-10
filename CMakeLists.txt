cmake_minimum_required(VERSION 3.26)
project(Graph_theory C)

set(CMAKE_C_STANDARD 23)

add_library(Graph_theory library.c
        main.c)
