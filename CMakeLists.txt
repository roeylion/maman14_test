cmake_minimum_required(VERSION 3.24)
project(maman14_test C)

set(CMAKE_C_STANDARD 90)

add_executable(maman14_test assembler.c tests.c)
