cmake_minimum_required(VERSION 3.10)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "sources/*.cpp")

add_executable(club ${SOURCES})