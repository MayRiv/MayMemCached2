cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

add_library(engine
    include/engine/IRequestController.hpp
    include/engine/RequestControllerFactory.hpp
    include/engine/IResponse.hpp
    src/RequestController.hpp
    src/RequestController.cpp
    src/RequestControllerFactory.cpp

    src/IRequestParser.hpp
    src/SimpleProto/SimpleRequestParser.hpp
    src/SimpleProto/SimpleRequestParser.cpp
    src/SimpleProto/LexemeParser.hpp
    src/SimpleProto/ILexemeParser.hpp
    src/SimpleProto/LexemeParser.cpp
    src/SimpleProto/Representations/SimpleEchoRepresentation.hpp
    src/SimpleProto/Representations/SimpleEchoRepresentation.cpp
    )
set_target_properties(engine PROPERTIES
    CXX_STANDARD 17)
target_link_libraries(engine logic)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

##testing to be moved in another CMakeLists
find_package(GTest REQUIRED)
find_package(Threads)

add_executable(engine_test test/SimpleProto/LexemeParser_test.hpp
                           test/TestLauncher.cpp
                           src/SimpleProto/LexemeParser.hpp
                           src/SimpleProto/ILexemeParser.hpp
                           src/SimpleProto/LexemeParser.cpp)


target_include_directories(engine_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

set_target_properties(engine_test PROPERTIES
                           CXX_STANDARD 17)
target_include_directories(engine_test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(engine_test ${GTEST_LIBRARIES})
target_link_libraries(engine_test ${CMAKE_THREAD_LIBS_INIT})

#add_subdirectory(test)

