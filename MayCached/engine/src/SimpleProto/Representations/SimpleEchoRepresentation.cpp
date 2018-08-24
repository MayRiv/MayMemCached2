
#include <SimpleProto/Representations/SimpleEchoRepresentation.hpp>
#include <logic/Answers/EchoAnswer.hpp>
namespace maycached {
namespace engine {

void SimpleEchoRepresentation::setAnswer(const logic::EchoAnswer &answer)
{
    m_Echo = answer.echoString;
}

std::string SimpleEchoRepresentation::serializeAnswerToString() const
{
    return "Echo:" + m_Echo;
}

} }
