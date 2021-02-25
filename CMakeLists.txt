cmake_minimum_required(VERSION 3.17)
project(GP_RAC)

set(CMAKE_CXX_STANDARD 20)

add_executable(GP_RAC main.cpp PM.cpp PM.h Container.cpp Container.h VM.cpp VM.h Rule.cpp Rule.h data.cpp data.h)