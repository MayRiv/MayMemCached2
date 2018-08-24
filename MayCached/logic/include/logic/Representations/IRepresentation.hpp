#ifndef IREPRESENTATION_HPP
#define IREPRESENTATION_HPP
#include <string>
namespace maycached {
namespace logic {
class IRepresentation
{
public:
    virtual std::string serializeAnswerToString() const = 0;
};

} }
#endif
