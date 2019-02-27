cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(maycached)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "D:/MayMemCached2/MayCached/toolset/boost_1_67_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/MayMemCached2/MayCached/toolset/boost_1_67_0/stage/lib")

set(Boost_DEBUG 1)

SET (BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}."toolset/boost_1_67_0" CACHE PATH "Boost library path")
#SET (BOOST_LIBRARYDIR "toolset/boost_1_67_0/stage/lib")
set(IncludeBoost  ${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_ROOT})
message(${IncludeBoost})
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
SET (BOOST_MIN_VERSION "1.67.0")

 
find_package(Boost REQUIRED COMPONENTS system thread regex)
include_directories(PUBLIC ${PROJECT_SOURCE_DIR} + "/toolset/boost_1_67_0/")

add_subdirectory(mainapp)
add_subdirectory(engine)
add_subdirectory(connection)
add_subdirectory(logic)
add_subdirectory(toolset)
add_subdirectory(system)
