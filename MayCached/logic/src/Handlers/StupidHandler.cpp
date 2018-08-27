#include <Handlers/StupidHandler.hpp>
#include <logic/Answers/EchoAnswer.hpp>
#include <logic/Commands/EchoCommand.hpp>
namespace maycached {
namespace logic {

void StupidHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        auto&& echoCommand = dynamic_cast<EchoCommand&>(command);

        echoCommand.setAnswer(EchoAnswer{echoCommand.getMessage()});

    }
}

} }

