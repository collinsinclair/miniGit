cmake_minimum_required(VERSION 3.19)
project(miniGit)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(miniGit
        driver.cpp
        miniGit.cpp
        miniGit.h)
