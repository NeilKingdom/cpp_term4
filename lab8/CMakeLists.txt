cmake_minimum_required(VERSION 3.2)
project("lab8")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library("jni.so" SHARED "jni.cpp" "jni.h")

target_include_directories(
    jni.so PRIVATE
    "/usr/lib/jvm/default/include"
    "/usr/lib/jvm/default/include/linux"
)
