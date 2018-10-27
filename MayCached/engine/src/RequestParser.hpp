#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H
#include <IRequestParser.hpp>
#include <SimpleProto/ILexemeParser.hpp>
#include <ICommandBuilder.hpp>
#include <RuleSet.hpp>
#include <list>
namespace maycached {
namespace engine {
class RequestParser: public IRequestParser
{
public:
    RequestParser();
    std::unique_ptr<logic::ICommand> parseCommand(const std::string& rawInput) override;

private:
    std::unique_ptr<logic::ICommand> buildCommand(std::vector<std::string>&& lexemes);
    void setUpRules();

    std::unique_ptr<ILexemeParser> m_LexemeParser;
    std::unique_ptr<ICommandBuilder> m_CommandBuilder;
    std::list<rules::RuleSet> rules;
};
} }
#endif
