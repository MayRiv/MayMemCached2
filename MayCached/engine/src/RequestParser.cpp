#include <RequestParser.hpp>
#include <logic/Commands/EchoCommand.hpp>
#include <SimpleProto/Representations/SimpleEchoRepresentation.hpp>
#include <SimpleProto/SimpleCommandBuilder.hpp>

#include <memory>
#include <SimpleProto/LexemeParser.hpp>
#include <functional>
#include <boost/algorithm/string.hpp>
namespace maycached {
namespace engine {

RequestParser::RequestParser()
{
    m_LexemeParser = std::make_unique<lexeme_parser::LexemeParser>();
    m_CommandBuilder = std::make_unique<SimpleCommandBuilder>();
    setUpRules();
}

std::unique_ptr<logic::ICommand> RequestParser::parseCommand(const std::string& rawInput)
{
    std::unique_ptr<logic::ICommand> command = nullptr;
    std::cout << "Input is " << rawInput << std::endl;
    auto result = m_LexemeParser->parse(rawInput);
    if (result.has_value())
    {
        auto&& lexemes = result.value();
        if (!lexemes.empty())
        {
            command = buildCommand(std::move(lexemes));
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
    return command;
}

std::unique_ptr<logic::ICommand> RequestParser::buildCommand(std::vector<std::string> &&lexemes)
{
    auto builder = std::find_if(rules.begin(), rules.end(), [&lexemes](rules::RuleSet rule){
        return rule.check(lexemes);
    });

    return (builder != rules.end() ? builder->build(lexemes) : nullptr);
}

void RequestParser::setUpRules()
{
    using namespace rules;
    RuleSet getRule;
    getRule.addRule([](RuleSet::Lexemes l){
        return l.size() == 2;
    })
           .addRule([](RuleSet::Lexemes l){
        return boost::to_upper_copy(l[0]) == "GET";
    })
           .setBuilder(std::bind(&ICommandBuilder::buildGetCommand, m_CommandBuilder.get(), std::placeholders::_1));

    RuleSet delRule;
    delRule.addRule([](RuleSet::Lexemes l){
        return l.size() == 2;
    })
           .addRule([](RuleSet::Lexemes l){
        return boost::to_upper_copy(l[0]) == "DEL";
    })
           .setBuilder(std::bind(&ICommandBuilder::buildDelCommand, m_CommandBuilder.get(), std::placeholders::_1));


    RuleSet setRule;
    setRule.addRule([](RuleSet::Lexemes l){
        return l.size() == 3 || l.size() == 4;
    })
           .addRule([](RuleSet::Lexemes l){
        return boost::to_upper_copy(l[0]) == "SET";
    })
           .addRule([](RuleSet::Lexemes l){
        return l.size() == 4 ? IS_DIGIT_N(l, 4) : true;
    })
           .setBuilder(std::bind(&ICommandBuilder::buildSetCommand, m_CommandBuilder.get(), std::placeholders::_1));

    RuleSet stopRule;
    stopRule.addRule([](RuleSet::Lexemes l){
        return l.size() == 1;
    })
           .addRule([](RuleSet::Lexemes l){
        return boost::to_upper_copy(l[0]) == "STOP";
    })
           .setBuilder(std::bind(&ICommandBuilder::buildStopCommand, m_CommandBuilder.get(), std::placeholders::_1));

    rules.push_back(getRule);
    rules.push_back(setRule);
    rules.push_back(delRule);
    rules.push_back(stopRule);
}




} }
