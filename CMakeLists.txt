cmake_minimum_required(VERSION 3.17)
project(XV6 C)

set(CMAKE_C_STANDARD 11)

add_executable(XV6 main.c *.c *.h)