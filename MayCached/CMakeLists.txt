cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(maycached)

SET (BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/toolset/boost_1_67_0 CACHE PATH "Boost library path")
SET (BOOST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/toolset/boost_1_67_0)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
SET (BOOST_MIN_VERSION "1.67.0")
message(${BOOST_INCLUDE})

find_package(Boost REQUIRED COMPONENTS system thread regex)

add_subdirectory(mainapp)
add_subdirectory(engine)
add_subdirectory(connection)
add_subdirectory(logic)
add_subdirectory(toolset)
add_subdirectory(system)
