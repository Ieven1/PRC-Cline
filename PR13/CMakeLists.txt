cmake_minimum_required(VERSION 3.28)
project(PR13 C)

set(CMAKE_C_STANDARD 11)

add_executable(PR13 main.c
        stack.c
        stack.h
        student.c
        student.h)
