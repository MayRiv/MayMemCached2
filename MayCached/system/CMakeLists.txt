cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(system)

add_library(${PROJECT_NAME}
    include/${PROJECT_NAME}/IThreadPool.hpp
    src/ThreadPool.hpp
    src/ThreadPool.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)
