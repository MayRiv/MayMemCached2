#ifndef IECHOREPRESENTATION_H
#define IECHOREPRESENTATION_H
#include <logic/Representations/IRepresentation.hpp>
#include <logic/Answers/EchoAnswer.hpp>

namespace maycached {
namespace logic {
class IEchoRepresentation: public IRepresentation
{
public:
    virtual void setAnswer(const EchoAnswer&  answer) = 0;
};

} }
#endif // IECHOREPRESENTATION_H
