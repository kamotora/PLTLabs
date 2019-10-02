cmake_minimum_required(VERSION 3.15)
project(compC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(compC__ main.cpp defs.h Scanner.h Scanner.cpp)