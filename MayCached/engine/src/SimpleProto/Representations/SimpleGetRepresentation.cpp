
#include <SimpleProto/Representations/SimpleGetRepresentation.hpp>
#include <logic/Answers/GetAnswer.hpp>
namespace maycached {
namespace engine {

void SimpleGetRepresentation::setAnswer(const logic::GetAnswer &answer)
{
    m_Answer = answer;
}

std::string SimpleGetRepresentation::serializeAnswerToString() const
{
    if (m_Answer.value.has_value())
    {
        return "VALUE: " + *m_Answer.value + "\r\n";
    }
    else
    {
        return "EMPTY\r\n";
    }
}

} }
