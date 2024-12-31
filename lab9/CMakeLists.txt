cmake_minimum_required(VERSION 3.2)
project("lab9")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_library("jni.so" SHARED "jni.cpp" "jni.h")

target_include_directories(
    "jni.so" PRIVATE
    "/usr/lib/jvm/default/include"
    "/usr/lib/jvm/default/include/linux"
)
