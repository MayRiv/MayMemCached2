cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

add_library(engine include/engine/IRequestController.hpp
    src/RequestController.hpp
    src/RequestController.cpp
    src/RequestControllerFactory.cpp
    include/engine/RequestControllerFactory.hpp
    )


target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

