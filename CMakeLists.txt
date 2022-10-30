cmake_minimum_required(VERSION 3.0.0)
project(matrixcalc)

set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wpedantic -Wextra -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS "--coverage -lgcov")
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(generator)
add_subdirectory(slice)
add_subdirectory(matrix)

target_link_libraries(${PROJECT_NAME} PUBLIC matrix)

enable_testing()
add_subdirectory(tests)