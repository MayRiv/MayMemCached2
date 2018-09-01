#ifndef SIMPLE_REQUEST_PARSER_H
#define SIMPLE_REQUEST_PARSER_H
#include <IRequestParser.hpp>
#include <SimpleProto/ILexemeParser.hpp>
namespace maycached {
namespace engine {
class SimpleRequestParser: public IRequestParser
{
public:
    SimpleRequestParser();
    std::unique_ptr<logic::ICommand> parseCommand(std::string rawInput) override;
private:
    std::unique_ptr<ILexemeParser> m_LexemeParser;
};
} }
#endif
