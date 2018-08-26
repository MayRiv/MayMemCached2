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
    src/SimpleProto/Representations/SimpleEchoRepresentation.hpp
    src/SimpleProto/Representations/SimpleEchoRepresentation.cpp
    )

set_target_properties(engine PROPERTIES
    CXX_STANDARD 17)
target_link_libraries(engine logic)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)


