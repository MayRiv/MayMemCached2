#include <SimpleProto/SimpleRequestParser.hpp>
#include <logic/Commands/EchoCommand.hpp>
#include <SimpleProto/Representations/SimpleEchoRepresentation.hpp>

#include <memory>
namespace maycached {
namespace engine {

std::unique_ptr<logic::ICommand> SimpleRequestParser::parseCommand(std::string rawInput)
{
    auto echoRepresentation = std::make_unique<SimpleEchoRepresentation>();
    auto echoCommand = std::make_unique<logic::EchoCommand>(std::move(echoRepresentation), rawInput);
    return echoCommand;
}

} }
