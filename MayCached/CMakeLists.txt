cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system thread regex)
function(custom_add_executable_from_dir TARGET)
    file(GLOB TARGET_SRC "CMAKE_CURRENT_SOURCE_DIR/*.cpp")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()
add_subdirectory(mainapp)
add_subdirectory(engine)
add_subdirectory(connection)
add_subdirectory(logic)
add_subdirectory(toolset)

add_subdirectory(system)
