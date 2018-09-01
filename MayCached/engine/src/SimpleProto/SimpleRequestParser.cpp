#include <SimpleProto/SimpleRequestParser.hpp>
#include <logic/Commands/EchoCommand.hpp>
#include <SimpleProto/Representations/SimpleEchoRepresentation.hpp>

#include <memory>
#include <SimpleProto/LexemeParser.hpp>
namespace maycached {
namespace engine {

SimpleRequestParser::SimpleRequestParser()
{
    m_LexemeParser = std::make_unique<lexeme_parser::LexemeParser>();
}

std::unique_ptr<logic::ICommand> SimpleRequestParser::parseCommand(std::string rawInput)
{
    std::cout << "Input is " << rawInput << std::endl;
    auto result = m_LexemeParser->parse(rawInput);
    if (result.has_value())
    {
        auto&& lexemes = result.value();
        if (!lexemes.empty())
        {
            for(auto& s : result.value())
            {
                std::cout << "Lexeme: " << s << std::endl;
            }
        }
        else
        {
            std::cout << "Empty lexemes" << std::endl;
        }
    }
    else
    {
        std::cout << "Parsing failed" << std::endl;
    }
    auto echoRepresentation = std::make_unique<SimpleEchoRepresentation>();
    auto echoCommand = std::make_unique<logic::EchoCommand>(std::move(echoRepresentation), rawInput);
    return echoCommand;
}

} }
