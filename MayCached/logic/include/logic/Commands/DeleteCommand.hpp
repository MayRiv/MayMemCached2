#ifndef DELETE_COMMAND_HPP
#define DELETE_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IStatusRepresentation.hpp>
#include <string>
#include <memory>
#include <gsl/pointers>
#include <optional>
namespace maycached {
namespace logic {
class DeleteCommand : public ICommand
{
public:

    DeleteCommand(std::unique_ptr<IStatusRepresentation>&& representation, const std::string& key):
        ICommand(ICommand::CommandType::E_DELETE,
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
        return "deletes value by key";
    }
private:
    std::unique_ptr<IStatusRepresentation> m_Representation;
    const std::string m_Key;
};

} }

#endif
