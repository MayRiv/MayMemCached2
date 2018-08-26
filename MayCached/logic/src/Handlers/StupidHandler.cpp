#include <Handlers/StupidHandler.hpp>
#include <logic/Answers/EchoAnswer.hpp>
#include <logic/Commands/EchoCommand.hpp>
namespace maycached {
namespace logic {

void StupidHandler::handle(const gsl::not_null<ICommand *> command)
{
    if (command->getType() == m_Type)
    {
        if (auto&& echoCommand = dynamic_cast<EchoCommand*>(command.get()))
        {
            echoCommand->setAnswer(EchoAnswer{echoCommand->getMessage()});
        }
    }
}

} }

