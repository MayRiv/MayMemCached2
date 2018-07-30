cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(connection)

add_library(${PROJECT_NAME}
    include/${PROJECT_NAME}/IServer.hpp
    src/Server.hpp
    src/Server.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)
