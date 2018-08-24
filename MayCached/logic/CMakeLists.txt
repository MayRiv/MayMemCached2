cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(logic)

add_library(${PROJECT_NAME}
    include/logic/IHandler.hpp
    include/logic/Commands/ICommand.hpp
    src/Handlers/StupidHandler.hpp
    src/Handlers/StupidHandler.cpp
    src/Handlers/VersionHandler.hpp
    src/Handlers/VersionHandler.cpp
    src/LogicController.cpp
    src/LogicController.hpp
    include/logic/LogicControllerFactory.hpp
    src/LogicControllerFactory.cpp
    include/logic/ILogicController.hpp
    include/logic/Commands/EchoCommand.hpp
    include/logic/Commands/EchoCommand.cpp
    include/logic/Commands/VersionCommand.hpp
    include/logic/Commands/VersionCommand.cpp

    include/logic/Representations/IRepresentation.hpp
    include/logic/Representations/IVersionRepresentation.hpp
    include/logic/Representations/IEchoRepresentation.hpp

    include/logic/Answers/VersionAnswer.hpp
    include/logic/Answers/EchoAnswer.hpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

