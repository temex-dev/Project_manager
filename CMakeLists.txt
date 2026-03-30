cmake_minimum_required(VERSION 3.10)
project(Project_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(main
    src/main.cpp
    src/Terminal.cpp
    src/Task.cpp
)
