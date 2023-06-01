cmake_minimum_required(VERSION 3.25)
project(card)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(card main.cpp SHA256.cpp SHA256.h)
