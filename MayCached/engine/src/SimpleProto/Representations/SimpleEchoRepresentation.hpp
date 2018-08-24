#ifndef SIMPLE_ECHO_REPRESENTATION_H
#define SIMPLE_ECHO_REPRESENTATION_H
#include <logic/Representations/IEchoRepresentation.hpp>
#include <string>


namespace maycached {
namespace engine {
class SimpleEchoRepresentation: public logic::IEchoRepresentation
{
public:
    void setAnswer(const logic::EchoAnswer&  answer) override;
    std::string serializeAnswerToString() const override;
private:
    std::string m_Echo;
};
} }
#endif
