cmake_minimum_required(VERSION 3.3)
project(test_queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        list_2cell.c
        list_2cell.h
        queue.c
        queue.h main.c)

add_executable(test_queue ${SOURCE_FILES} main.c)