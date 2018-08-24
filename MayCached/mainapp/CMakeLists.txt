cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(MayCached VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} connection)

target_link_libraries(${PROJECT_NAME} engine)

target_link_libraries(${PROJECT_NAME} logic)

