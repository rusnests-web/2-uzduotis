cmake_minimum_required(VERSION 3.13)

project(studentu_programa LANGUAGES CXX)

add_executable(studentu_programa
    pradinis.cpp
    funkcijos.cpp
    mediana.cpp
    studentas.cpp
)

set_target_properties(studentu_programa PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
