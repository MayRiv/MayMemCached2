cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(connection)

add_library(connection
    include/connection/IServer.hpp
    include/connection/ServerFactory.hpp
    src/Server.hpp
    src/Server.cpp
    src/ClientSession.hpp
    src/ClientSession.cpp
    src/ServerFactory.cpp
    )


target_include_directories(connection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_link_libraries(connection ${Boost_LIBRARIES})


target_link_libraries(connection engine)
