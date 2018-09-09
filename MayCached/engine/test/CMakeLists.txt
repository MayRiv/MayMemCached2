cmake_minimum_required(VERSION 3.2 FATAL_ERROR)


find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(engine_test SimpleProto/LexemeParser_test.cpp
                           TestLauncher.cpp)

target_link_libraries(engine ${GTEST_LIBRARIES})

target_link_libraries(engine ${CMAKE_THREAD_LIBS_INIT})
