#ifndef ILEXEME_PARSER_H
#define ILEXEME_PARSER_H
#include <optional>
#include <vector>
#include <string>
namespace maycached {
namespace engine {
class ILexemeParser
{
public:
    virtual std::optional<std::vector<std::string>> parse(std::string input) = 0;
};
} }
#endif
