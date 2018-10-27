#ifndef IREQUEST_PARSER_H
#define IREQUEST_PARSER_H
#include <logic/Commands/ICommand.hpp>
#include <memory>
namespace maycached {
namespace engine {
class IRequestParser
{
public:
    virtual std::unique_ptr<logic::ICommand> parseCommand(const std::string& rawInput) = 0;
};
} }
#endif
