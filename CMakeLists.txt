cmake_minimum_required(VERSION 3.28)
project(c_sandbox C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c util/str_util.h)

add_executable(c_sandbox main.c
        permission.h
        util/str_util.h
        can.c
)
