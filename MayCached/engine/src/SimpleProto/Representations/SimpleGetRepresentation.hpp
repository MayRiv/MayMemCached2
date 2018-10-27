#ifndef SIMPLE_GET_REPRESENTATION_H
#define SIMPLE_GET_REPRESENTATION_H
#include <logic/Representations/IGetRepresentation.hpp>
#include <string>


namespace maycached {
namespace engine {
class SimpleGetRepresentation: public logic::IGetRepresentation
{
public:
    void setAnswer(const logic::GetAnswer&  answer) override;
    std::string serializeAnswerToString() const override;
private:
    logic::GetAnswer m_Answer;
};
} }
#endif
