cmake_minimum_required(VERSION 3.2)

project("Week1")

add_executable(Neil_Lab1 "Week1.cpp" "Week1.h")

set_property(TARGET Neil_Lab1 PROPERTY CXX_STANDARD 11)
set_property(TARGET Neil_Lab1 PROPERTY CXX_STANDARD_REQUIRED ON)
