cmake_minimum_required(VERSION 3.7.2)

project(06.homework)

add_executable(main main.cpp)
set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(tests)


