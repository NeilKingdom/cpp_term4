cmake_minimum_required(VERSION 3.13)
project(lab9)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_library(Week9_JNIDemo SHARED Week9_JNIDemo.cpp Week9_JNIDemo.h)

target_include_directories(Week9_JNIDemo PRIVATE
                          "/usr/lib/jvm/java-17-openjdk/include"
                          "/usr/lib/jvm/java-17-openjdk/include/linux")