#include <Handlers/StupidHandler.hpp>
#include <logic/Answers/EchoAnswer.hpp>
#include <logic/Commands/EchoCommand.hpp>
namespace maycached {
namespace logic {

void StupidHandler::handle(const std::weak_ptr<ICommand>& command)
{
    if (auto&& c = command.lock())
    {
        if (c->getType() == m_Type)
        {
            if (auto&& echoCommand = dynamic_cast<EchoCommand*>(c.get()))
            {
                echoCommand->setAnswer(EchoAnswer{echoCommand->getMessage()});
            }
        }
    }
}

} }

