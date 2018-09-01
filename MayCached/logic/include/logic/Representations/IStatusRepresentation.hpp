#ifndef I_STATUS_REPRESENTATION_H
#define I_STATUS_REPRESENTATION_H
#include <logic/Representations/IRepresentation.hpp>
#include <logic/Answers/StatusAnswer.hpp>

namespace maycached {
namespace logic {
class IStatusRepresentation: public IRepresentation
{
public:
    virtual void setAnswer(const StatusAnswer&  answer) = 0;
};

} }
#endif // IECHOREPRESENTATION_H
