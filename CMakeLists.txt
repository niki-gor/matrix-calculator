cmake_minimum_required(VERSION 3.0.0)

project(matrixcalculator)

set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wpedantic -Wextra")
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(matrix)
add_subdirectory(rowcolumn)
add_subdirectory(rowcolumnlist)

target_link_libraries(${PROJECT_NAME} PUBLIC matrix rowcolumn rowcolumnlist)