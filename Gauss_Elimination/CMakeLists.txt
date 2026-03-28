cmake_minimum_required(VERSION 3.20)

project(Gauss_Elimination)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Gauss_Elimination
        main.cpp
        Matrix.cpp
)