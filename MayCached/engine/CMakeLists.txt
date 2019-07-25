cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

file (GLOB ${PROJECT_NAME}_src
    "*.hpp"
    "*.cpp"
    "include/*.hpp"
    "src/*.hpp"
    "src/*.cpp"
    "include/engine/*.hpp"
    "include/engine/*.cpp"
    "src/SimpleProto/*.hpp"
    "src/SimpleProto/*.cpp"
    "src/SimpleProto/Representations/*.hpp"
    "src/SimpleProto/Representations/*.cpp"
    "include/logic/Answers/*.hpp")
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_src})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} logic)
target_link_libraries(${PROJECT_NAME} system_tools)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_INCLUDE})
target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_ROOT})
#message(${IncludeBoost})


#[[
enable_testing()
add_executable(${PROJECT_NAME}_test test/SimpleProto/LexemeParser_test.hpp
                           test/TestLauncher.cpp
                           src/SimpleProto/LexemeParser.hpp
                           src/SimpleProto/ILexemeParser.hpp
                           src/SimpleProto/LexemeParser.cpp)


target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_include_directories(${PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include PRIVATE ${gtest_SOURCE_DIR})

set_target_properties(${PROJECT_NAME}_test PROPERTIES
                           CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)
target_include_directories(${PROJECT_NAME}_test PUBLIC ${IncludeBoost})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${BOOST_INCLUDE})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${BOOST_ROOT})
add_test(runEngineUnitTest ${PROJECT_NAME}_test)
]]
