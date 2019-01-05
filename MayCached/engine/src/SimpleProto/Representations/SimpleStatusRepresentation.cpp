
#include <SimpleProto/Representations/SimpleStatusRepresentation.hpp>
#include <logic/Answers/StatusAnswer.hpp>
namespace maycached {
namespace engine {

void SimpleStatusRepresentation::setAnswer(const logic::StatusAnswer &answer)
{
    m_Status = answer;
}

std::string SimpleStatusRepresentation::serializeAnswerToString() const
{
    std::string result = "OK";;
    switch (m_Status.status) {
    case logic::StatusAnswer::Status::E_UNKONWN_ERROR:
        result = "Unknown error";
        break;
    default:
        break;
    }
    return result  + "\r\n";
}

} }
