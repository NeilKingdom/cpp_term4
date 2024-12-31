cmake_minimum_required(VERSION 3.2)

project("lab1")

add_executable("main" "main.cpp" "main.h")

set_property(TARGET "main" PROPERTY CXX_STANDARD 14)
set_property(TARGET "main" PROPERTY CXX_STANDARD_REQUIRED ON)
