#ifndef LEXEME_PARSER_H_H
#define LEXEME_PARSER_H
#include "ILexemeParser.hpp"

#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <optional>
#include <vector>
namespace maycached {
namespace engine {
namespace lexeme_parser {
namespace sc = boost::statechart;
namespace mpl = boost::mpl;
struct ParsedCharacter : sc::event<ParsedCharacter>
{
    ParsedCharacter(char character): m_Character(character){}
    const char& getCh() const{
        return m_Character;
    }
private:
    char m_Character;
};
struct ParsedSpace : sc::event<ParsedSpace>
{};

struct ParsedQuotation : sc::event<ParsedQuotation>
{};

struct ParsedSlash: sc::event<ParsedSlash>
{};



struct SpaceSeparatorState;
struct QuotationSeparatorState;
struct SlashOccuredState;
struct LexemeParser: public ILexemeParser, sc::state_machine<LexemeParser, SpaceSeparatorState>
{

public:
    enum class StateMapping
    {
        SpaceSeparatorState = 0,
        QuotationSeparatorState,
        SlashOccuredState
    };

    std::optional<std::vector<std::string>> parse(const std::string& input) override;
    LexemeParser():
        m_PreviousState(StateMapping::SpaceSeparatorState),
        m_ParsedSuccessfully(true)
    {
        m_Tokens.push_back({""});
        initiate();
    }
    std::vector<std::string>& tokens(){
        return m_Tokens;
    }
    StateMapping& previousState(){
        return m_PreviousState;
    }
    bool& parsedSuccesfully(){
        return m_ParsedSuccessfully;
    }
private:
    std::vector<std::string> m_Tokens;
    StateMapping m_PreviousState;
    bool m_ParsedSuccessfully;
};

struct SpaceSeparatorState: sc::simple_state<SpaceSeparatorState, LexemeParser>
{
    typedef mpl::list<
        sc::custom_reaction<ParsedCharacter>,
        sc::custom_reaction<ParsedQuotation>,
        sc::custom_reaction<ParsedSpace>,
        sc::custom_reaction<ParsedSlash>
    > reactions;
    sc::result react(const ParsedCharacter pc);
    sc::result react(const ParsedQuotation);
    sc::result react(const ParsedSpace);
    sc::result react(const ParsedSlash);
};
struct QuotationSeparatorState:  sc::simple_state<QuotationSeparatorState, LexemeParser>
{
    typedef mpl::list<
        sc::custom_reaction<ParsedCharacter>,
        sc::custom_reaction<ParsedQuotation>,
        sc::custom_reaction<ParsedSpace>,
        sc::custom_reaction<ParsedSlash>
    > reactions;
    QuotationSeparatorState(){
    }
    sc::result react(const ParsedCharacter pc);
    sc::result react(const ParsedSpace);
    sc::result react(const ParsedQuotation);
    sc::result react(const ParsedSlash);
};

struct SlashOccuredState:  sc::simple_state<SlashOccuredState, LexemeParser>
{
    typedef mpl::list<
        sc::custom_reaction<ParsedCharacter>,
        sc::custom_reaction<ParsedQuotation>,
        sc::custom_reaction<ParsedSpace>,
        sc::custom_reaction<ParsedSlash>
    > reactions;

    sc::result react(const ParsedCharacter pc);
    sc::result react(const ParsedSpace);
    sc::result react(const ParsedQuotation);
    sc::result react(const ParsedSlash);
private:
    sc::result toPreviousOne();
};

} } }
#endif
