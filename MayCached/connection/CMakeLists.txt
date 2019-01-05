cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(connection)

file (GLOB ${PROJECT_NAME}_src
    "*.hpp"
    "*.cpp"
    "include/*.hpp"
    "src/*.hpp"
    "src/*.cpp"
    "include/connection/*.hpp"
    "include/connection/*.cpp")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


target_link_libraries(${PROJECT_NAME} engine)


