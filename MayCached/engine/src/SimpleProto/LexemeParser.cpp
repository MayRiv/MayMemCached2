#include <SimpleProto/LexemeParser.hpp>
namespace maycached {
namespace engine {

std::optional<std::vector<std::string> > lexeme_parser::LexemeParser::parse(const std::string &input)
{
    for(auto& ch : input)
    {
        switch (ch) {
        case ' ' :
            process_event(ParsedSpace());
            break;
        case '"' :
            process_event(ParsedQuotation());
            break;
        case '\\':
            process_event(ParsedSlash());
            break;
        default:
            process_event(ParsedCharacter(ch));
        }

    }
    if (m_ParsedSuccessfully)
    {

        return m_Tokens;
    }
    else
    {
        return std::nullopt;
    }
}

boost::statechart::result lexeme_parser::SpaceSeparatorState::react(const lexeme_parser::ParsedCharacter pc)
{
    auto& tokens = context<LexemeParser>().tokens();
    tokens.back().push_back(pc.getCh());
    return transit<SpaceSeparatorState>();
}

boost::statechart::result lexeme_parser::SpaceSeparatorState::react(const lexeme_parser::ParsedQuotation)
{
    auto& tokens = context<LexemeParser>().tokens();
    if (tokens.back() != "")
    {
        tokens.push_back({""});
    }
    context<LexemeParser>().parsedSuccesfully() = false; //waiting for closing "
    context<LexemeParser>().previousState() = LexemeParser::StateMapping::SpaceSeparatorState;
    return transit<QuotationSeparatorState>();
}

boost::statechart::result lexeme_parser::SpaceSeparatorState::react(const lexeme_parser::ParsedSpace)
{
    auto& tokens = context<LexemeParser>().tokens();
    if (tokens.back() != "")
    {
        tokens.push_back({""});
    }
    return transit<SpaceSeparatorState>();
}

boost::statechart::result lexeme_parser::SpaceSeparatorState::react(const lexeme_parser::ParsedSlash)
{
    context<LexemeParser>().parsedSuccesfully() = false; //waiting for the symbol
    context<LexemeParser>().previousState() = LexemeParser::StateMapping::SpaceSeparatorState;
    return transit<SlashOccuredState>();
}

boost::statechart::result lexeme_parser::QuotationSeparatorState::react(const lexeme_parser::ParsedCharacter pc)
{
    auto& tokens = context<LexemeParser>().tokens();
    tokens.back().push_back(pc.getCh());
    return transit<QuotationSeparatorState>();
}

boost::statechart::result lexeme_parser::QuotationSeparatorState::react(const lexeme_parser::ParsedSpace)
{
    auto& tokens = context<LexemeParser>().tokens();
    if (tokens.back().back() != ' ')
    {
        tokens.back().push_back(' ');
    }
    return transit<QuotationSeparatorState>();
}

boost::statechart::result lexeme_parser::QuotationSeparatorState::react(const lexeme_parser::ParsedQuotation)
{
    context<LexemeParser>().parsedSuccesfully() = true;
    context<LexemeParser>().previousState() = LexemeParser::StateMapping::QuotationSeparatorState;
    return transit<SpaceSeparatorState>();
}

boost::statechart::result lexeme_parser::QuotationSeparatorState::react(const lexeme_parser::ParsedSlash)
{
    context<LexemeParser>().previousState() = LexemeParser::StateMapping::QuotationSeparatorState;
    return transit<SlashOccuredState>();
}

boost::statechart::result lexeme_parser::SlashOccuredState::react(const lexeme_parser::ParsedCharacter pc)
{
    auto& tokens = context<LexemeParser>().tokens();
    tokens.back().push_back(pc.getCh());
    return toPreviousOne();
}

boost::statechart::result lexeme_parser::SlashOccuredState::react(const lexeme_parser::ParsedSpace)
{
    context<LexemeParser>().tokens().back().push_back(' ');
    return toPreviousOne();
}

boost::statechart::result lexeme_parser::SlashOccuredState::react(const lexeme_parser::ParsedQuotation)
{
    context<LexemeParser>().tokens().back().push_back('"');
    return toPreviousOne();
}

boost::statechart::result lexeme_parser::SlashOccuredState::react(const lexeme_parser::ParsedSlash)
{
    context<LexemeParser>().tokens().back().push_back('\\');
    return toPreviousOne();
}

boost::statechart::result lexeme_parser::SlashOccuredState::toPreviousOne(){
    switch (context<LexemeParser>().previousState()) {
    case LexemeParser::StateMapping::SpaceSeparatorState:
        context<LexemeParser>().parsedSuccesfully() = true;
        return transit<SpaceSeparatorState>();
    case LexemeParser::StateMapping::QuotationSeparatorState:
        return transit<QuotationSeparatorState>();
    case LexemeParser::StateMapping::SlashOccuredState:
        assert(false); //should never happend
        return transit<SpaceSeparatorState>();
    }
}


} }
