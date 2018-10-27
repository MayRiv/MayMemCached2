#ifndef SIMPLE_STATUS_REPRESENTATION_H
#define SIMPLE_STATUS_REPRESENTATION_H
#include <logic/Answers/StatusAnswer.hpp>
#include <logic/Representations/IStatusRepresentation.hpp>
#include <string>


namespace maycached {
namespace engine {
class SimpleStatusRepresentation: public logic::IStatusRepresentation
{
public:
    void setAnswer(const logic::StatusAnswer&  answer) override;
    std::string serializeAnswerToString() const override;
private:
    logic::StatusAnswer m_Status;
};
} }
#endif
