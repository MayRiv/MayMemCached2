#ifndef I_GET_REPRESENTATION_H
#define I_GET_REPRESENTATION_H
#include <logic/Representations/IRepresentation.hpp>
#include <logic/Answers/GetAnswer.hpp>

namespace maycached {
namespace logic {
class IGetRepresentation: public IRepresentation
{
public:
    virtual void setAnswer(const GetAnswer&  answer) = 0;
};

} }
#endif // IECHOREPRESENTATION_H
