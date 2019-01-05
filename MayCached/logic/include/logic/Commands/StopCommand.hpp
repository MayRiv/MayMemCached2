#ifndef STOP_COMMAND_HPP
#define STOP_COMMAND_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/Representations/IStatusRepresentation.hpp>
#include <string>
#include <memory>
#include <gsl/pointers>
namespace maycached {
namespace logic {
class StopCommand : public ICommand
{
public:

    StopCommand(std::unique_ptr<IStatusRepresentation>&& representation):
        ICommand(ICommand::CommandType::E_STOP,
                 static_cast<gsl::not_null<IRepresentation*>>(representation.get())),
        m_Representation(std::move(representation))
    {}
    template <class T>
    void setAnswer(T&& answer){
        m_Representation->setAnswer(std::forward<T&&>(answer));
    }
    std::string getDescription() override {
        return "Shutdowns the application";
    }
private:

    std::unique_ptr<IStatusRepresentation> m_Representation;
};

} }

#endif
