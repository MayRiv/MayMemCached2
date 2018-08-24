#ifndef IVERSION_REPRESENTATION_HPP
#define IVERSION_REPRESENTATION_HPP
#include <logic/Representations/IRepresentation.hpp>
#include <logic/Answers/VersionAnswer.hpp>
namespace maycached {
namespace logic {
class IVersionRepresentation: public IRepresentation
{
public:
    virtual void setAnswer(const VersionAnswer&  answer) = 0;
};

} }
#endif
