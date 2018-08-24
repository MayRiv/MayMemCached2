#ifndef ECHO_COMMAND_HPP
#define ECHO_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IEchoRepresentation.hpp>
#include <string>
#include <memory>
namespace maycached {
namespace logic {
class EchoCommand : public ICommand
{
public:

    EchoCommand(std::unique_ptr<IEchoRepresentation>&& representation, const std::string& message):
        ICommand(ICommand::CommandType::E_ECHO, *representation),
        m_Representation(std::move(representation)),
        m_Message(message)
    {}
    template <class T>
    void setAnswer(T&& answer){
        m_Representation->setAnswer(std::forward<T&&>(answer));
    }
    const std::string& getMessage() const;
    std::string getDescription() override {
        return "Returns copy of inputed string";
    }
private:

    std::unique_ptr<IEchoRepresentation> m_Representation;
    std::string m_Message;
};

} }

#endif
