#ifndef SIMPLE_REQUEST_PARSER_H
#define SIMPLE_REQUEST_PARSER_H
#include <IRequestParser.hpp>
namespace maycached {
namespace engine {
class SimpleRequestParser: public IRequestParser
{
public:
    std::unique_ptr<logic::ICommand> parseCommand(std::string rawInput) override;
};
} }
#endif
