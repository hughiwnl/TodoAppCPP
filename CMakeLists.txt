cmake_minimum_required(VERSION 3.25)
project(todo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(todo
  src/main.cpp
  src/todo.cpp
)
