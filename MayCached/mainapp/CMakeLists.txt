cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(MayCached VERSION 0.1 LANGUAGES CXX)


file (GLOB ${PROJECT_NAME}_src
    "*.hpp"
    "*.cpp"
    "SUSD/*.hpp"
    "SUSD/*.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_src})

target_link_libraries(${PROJECT_NAME} connection)

target_link_libraries(${PROJECT_NAME} engine)

target_link_libraries(${PROJECT_NAME} logic)
target_link_libraries(${PROJECT_NAME} system_tools)

target_include_directories(${PROJECT_NAME}
    PRIVATE SUSD)
