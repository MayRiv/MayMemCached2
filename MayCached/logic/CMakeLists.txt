cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(logic)

file (GLOB ${PROJECT_NAME}_src
    "*.hpp"
    "*.cpp"
    "include/*.hpp"
    "src/*.hpp"
    "src/*.cpp"
    "src/Handlers/*.hpp"
    "src/Handlers/*.cpp"
    "src/Database/*.hpp"
    "src/Database/*.cpp"
    "include/logic/Representations/*.hpp"
    "include/logic/Representations/*.cpp"
    "include/logic/Commands/*.hpp"
    "include/logic/Commands/*.cpp"

    "include/logic/Answers/*.hpp")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_src})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_link_libraries(${PROJECT_NAME} GSL)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} system_tools)
#[[
enable_testing()

add_executable(${PROJECT_NAME}_test  test/TimeExpirationManagerTest.hpp
                           test/TimeExpirationCoreTest.hpp
                           src/TimeExpirationCore.hpp
                           src/TimeExpirationCore.cpp
                           src/TimeExpirationManager.hpp
                           src/TimeExpirationManager.cpp
                           src/Storage.hpp
                           src/Storage.cpp
                           src/IStorage.hpp
                           test/DatabaseMarshallerTest.hpp
                           src/Database/DataMarshallerRawBinary.hpp
                           src/Database/DataMarshallerRawBinary.cpp
                           src/Database/IDataMarshaller.hpp
                           src/Data.hpp
                           test/InMemorySerializationStrategyTest.hpp
                           src/Database/InMemorySerializationStrategy.hpp
                           src/Database/InMemorySerializationStrategy.cpp
                           test/TestLauncher.cpp
                           )

target_include_directories(${PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include PRIVATE ${gtest_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)



set_target_properties(${PROJECT_NAME}_test PROPERTIES
                           CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)

add_test(runLogicUnitTest ${PROJECT_NAME}_test)
]]