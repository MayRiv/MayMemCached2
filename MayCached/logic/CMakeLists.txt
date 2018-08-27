cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(logic)

add_library(${PROJECT_NAME}
    include/logic/IHandler.hpp
    include/logic/Commands/ICommand.hpp
    src/Handlers/StupidHandler.hpp
    src/Handlers/StupidHandler.cpp
    src/Handlers/VersionHandler.hpp
    src/Handlers/VersionHandler.cpp
    src/Handlers/SetHandler.hpp
    src/Handlers/SetHandler.cpp
    src/Handlers/GetHandler.hpp
    src/Handlers/GetHandler.cpp
    src/Storage.hpp
    src/Storage.cpp
    src/IStorage.hpp
    src/Data.hpp

    src/LogicController.cpp
    src/LogicController.hpp
    include/logic/LogicControllerFactory.hpp
    src/LogicControllerFactory.cpp
    include/logic/ILogicController.hpp
    include/logic/Commands/EchoCommand.hpp
    include/logic/Commands/EchoCommand.cpp
    include/logic/Commands/VersionCommand.hpp
    include/logic/Commands/VersionCommand.cpp
    include/logic/Commands/GetCommand.hpp
    include/logic/Commands/GetCommand.cpp
    include/logic/Commands/SetCommand.hpp
    include/logic/Commands/SetCommand.cpp

    include/logic/Representations/IRepresentation.hpp
    include/logic/Representations/IVersionRepresentation.hpp
    include/logic/Representations/IEchoRepresentation.hpp
    include/logic/Representations/IStatusRepresentation.hpp
    include/logic/Representations/IGetRepresentation.hpp

    include/logic/Answers/VersionAnswer.hpp
    include/logic/Answers/EchoAnswer.hpp
    include/logic/Answers/StatusAnswer.hpp
    include/logic/Answers/GetAnswer.hpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE src)

target_link_libraries(logic GSL)
set_target_properties(logic PROPERTIES
    CXX_STANDARD 17)
