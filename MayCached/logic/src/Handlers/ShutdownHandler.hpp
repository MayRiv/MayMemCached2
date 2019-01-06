#ifndef SHUTDOWN_HANDLER_HPP
#define SHUTDOWN_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
#include <gsl/pointers>
#include <system/IMainappStopper.hpp>
namespace maycached {
namespace logic {
class ShutdownHandler: public  IHandler
{
public:
    ShutdownHandler(gsl::not_null<system::IMainappStopper*> stopper):
        m_Type(ICommand::CommandType::E_STOP),
        m_Stopper(stopper)
    {}
    void handle(ICommand &command) override;

private:
    ICommand::CommandType m_Type;
    gsl::not_null<system::IMainappStopper*> m_Stopper;
};

} }
#endif
