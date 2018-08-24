#include <Handlers/VersionHandler.hpp>
#include <logic/Answers/VersionAnswer.hpp>
#include <logic/Commands/VersionCommand.hpp>
namespace maycached {
namespace logic {

void VersionHandler::handle(const std::weak_ptr<ICommand> &command)
{
    if (auto&& c = command.lock())
    {
        if (c->getType() == m_Type)
        {
            if (auto&& versionCommand = dynamic_cast<VersionCommand*>(c.get()))
            {
                versionCommand->setAnswer(VersionAnswer{1,1});
            }
        }
    }
}

} }

