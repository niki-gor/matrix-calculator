project(tests)

find_package(GTest REQUIRED)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC generator slice matrix GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})