#include <Handlers/ShutdownHandler.hpp>
#include <logic/Answers/StatusAnswer.hpp>
#include <logic/Commands/StopCommand.hpp>
namespace maycached {
namespace logic {

void ShutdownHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        auto&& stopCommand = dynamic_cast<StopCommand&>(command);
        stopCommand.setAnswer(StatusAnswer{ StatusAnswer::Status::E_SUCCESS });

        m_Stopper->launchMainApplicationShutdown();

    }
    else
    {
        pass(command);
    }
}

} }

