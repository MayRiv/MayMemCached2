cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system thread regex)

add_subdirectory(connection)
add_subdirectory(mainapp)
add_subdirectory(engine)
add_subdirectory(logic)
add_subdirectory(system)
