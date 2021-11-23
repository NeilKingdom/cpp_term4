cmake_minimum_required(VERSION 3.13)
project(lab8)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Week8_JNIDemo.so SHARED Week8_JNIDemo.cpp Week8_JNIDemo.h)

target_include_directories(Week8_JNIDemo.so PRIVATE
                          "/usr/lib/jvm/java-11-openjdk/include"
                          "/usr/lib/jvm/java-11-openjdk/include/linux")