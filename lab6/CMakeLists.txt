
cmake_minimum_required(VERSION 3.2)

project("main")

add_executable("hello" "main.cpp" "vehicle.h" "vehicle.cpp" "electric_vehicle.cpp" "electric_vehicle.h" "gasoline_vehicle.cpp" "gasoline_vehicle.h" "hybrid_vehicle.cpp" "hybrid_vehicle.h")
