#ifndef GET_COMMAND_HPP
#define GET_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IGetRepresentation.hpp>
#include <string>
#include <memory>
#include <gsl/pointers>
namespace maycached {
namespace logic {
class GetCommand : public ICommand
{
public:

    GetCommand(std::unique_ptr<IGetRepresentation>&& representation, const std::string& key):
        ICommand(ICommand::CommandType::E_GET,
                 static_cast<gsl::not_null<IRepresentation*>>(representation.get())),
        m_Representation(std::move(representation)),
        m_Key(key)
    {}
    template <class T>
    void setAnswer(T&& answer){
        m_Representation->setAnswer(std::forward<T&&>(answer));
    }
    const std::string& getKey() const;
    std::string getDescription() override {
        return "Returns value by key";
    }
private:

    std::unique_ptr<IGetRepresentation> m_Representation;
    std::string m_Key;
};

} }

#endif
