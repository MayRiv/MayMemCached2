#ifndef VERSION_COMMAND_HPP
#define VERSION_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IVersionRepresentation.hpp>
#include <memory>
namespace maycached {
namespace logic {
class VersionCommand: public ICommand
{
public:
    VersionCommand(std::unique_ptr<IVersionRepresentation>&& representation):
        ICommand(ICommand::E_VERSION,
                 static_cast<gsl::not_null<IRepresentation*>>(representation.get())),
        m_Representation(std::move(representation))
    {
    }
    template <class T>
    void setAnswer(T&& answer){
        m_Representation->setAnswer(std::forward<T&&>(answer));
    }
    std::string getDescription() override{
        return "Returns version of application";
    }
private:
    std::unique_ptr<IVersionRepresentation> m_Representation;
};

} }
#endif
