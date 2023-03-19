cmake_minimum_required(VERSION 3.16)
project(Ex1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ex1 book.c Demo.c Person.c AdptArray.h Person.c Person.h AdptArray.c)
