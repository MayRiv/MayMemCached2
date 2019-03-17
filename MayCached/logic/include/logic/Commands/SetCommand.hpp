#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IStatusRepresentation.hpp>
#include <string>
#include <memory>
#include <gsl/pointers>
#include <optional>
namespace maycached {
namespace logic {
class SetCommand : public ICommand
{
public:

    SetCommand(std::unique_ptr<IStatusRepresentation>&& representation, const std::string& key,
               const std::string& value, const std::optional<uint32_t> expires):
        ICommand(ICommand::CommandType::E_SET,
                 static_cast<gsl::not_null<IRepresentation*>>(representation.get())),
        m_Representation(std::move(representation)),
        m_Key(key),
        m_Value(value),
        m_Expires(expires)
    {}
    template <class T>
    void setAnswer(T&& answer){
        m_Representation->setAnswer(std::forward<T&&>(answer));
    }
    const std::string& getKey() const;

    const std::string& getValue() const;

    std::optional<uint32_t> getExprires() const;
    std::string getDescription() override {
        return "Sets the value by key";
    }
private:

    std::unique_ptr<IStatusRepresentation> m_Representation;
    const std::string m_Key;
    const std::string m_Value;
    const std::optional<uint32_t> m_Expires;
};

} }

#endif
