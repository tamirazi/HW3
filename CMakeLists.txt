cmake_minimum_required(VERSION 3.9)
project(HW3)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW3 main.cpp Model.cpp Model.h View.cpp View.h Controller.cpp Controller.h Geometry.cpp Geometry.h SimObject.cpp SimObject.h Port.cpp Port.h)