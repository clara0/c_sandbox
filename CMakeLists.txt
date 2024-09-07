cmake_minimum_required(VERSION 3.28)
project(c_sandbox C)

set(CMAKE_C_STANDARD 11)

add_executable(c_sandbox
        util/str_util.h
        can.c
        permission.h
        main.c
)
