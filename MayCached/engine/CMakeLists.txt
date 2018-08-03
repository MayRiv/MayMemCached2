cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

add_library(engine
    include/engine/IRequestController.hpp
    include/engine/RequestControllerFactory.hpp
    include/engine/IResponse.hpp
    src/RequestController.hpp
    src/RequestController.cpp
    src/RequestControllerFactory.cpp
    src/StupidResponse.hpp
    src/StupidResponse.cpp

    )


target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

