cmake_minimum_required(VERSION 3.15)
project(compC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(compC__ main.cpp defs.h Scanner.h Scanner.cpp Diagram.cpp Diagram.h Tree.cpp Tree.h defs.cpp LL1.cpp LL1.h Semant.cpp Semant.h)