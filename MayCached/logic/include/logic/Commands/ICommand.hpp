#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP
#include <logic/Representations/IRepresentation.hpp>
#include <memory>
#include <gsl/pointers>
namespace maycached {
namespace logic {
class ICommand
{
public:
    enum CommandType
    {
        E_ECHO = 0,
        E_GET,
        E_SET,
        E_VERSION,
        E_MAX
    };
    ICommand(CommandType type, const gsl::not_null<IRepresentation*> representation): m_Type(type), m_Representation(representation)
    {}

    CommandType getType(){
        return m_Type;
    }
    std::string getAnswer() const
    {
        return m_Representation->serializeAnswerToString();
    }
    virtual std::string getDescription(){
        return "No description";
    }
private:
    CommandType m_Type;
    const gsl::not_null<IRepresentation*> m_Representation;
};

} }
#endif
