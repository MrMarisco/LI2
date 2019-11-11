cmake_minimum_required(VERSION 3.13)
project(coisasfinais C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(coisasfinais
        estado.c
        estado.h
        main.c)
