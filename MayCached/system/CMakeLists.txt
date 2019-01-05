cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(system)

file (GLOB ${PROJECT_NAME}_src
    "*.hpp"
    "*.cpp"
    "include/system/*.hpp"
    "src/*.hpp"
    "src/*.cpp"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)
