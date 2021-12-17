cmake_minimum_required(VERSION 3.21)
project(NanaTest VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  nana
  GIT_REPOSITORY https://github.com/cnjinhao/nana.git
  GIT_TAG        v1.7.4
  GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(nana)

add_executable(CarRentalSystem Controller.cpp Customer.cpp RentalGUI.cpp RentalLocation.cpp ReturnGUI.cpp Vehicle.cpp ViewGUI.cpp ReturnGroup.cpp Controller.h Customer.h RentalGUI.h RentalLocation.h ReturnGUI.h Vehicle.h ViewGUI.h ReturnGroup.h)
target_link_libraries(CarRentalSystem PRIVATE nana)
