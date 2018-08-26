#include <Handlers/VersionHandler.hpp>
#include <logic/Answers/VersionAnswer.hpp>
#include <logic/Commands/VersionCommand.hpp>
namespace maycached {
namespace logic {

void VersionHandler::handle(const gsl::not_null<ICommand*> command)
{
    if (command->getType() == m_Type)
    {
        if (auto&& versionCommand = dynamic_cast<VersionCommand*>(command.get()))
        {
            versionCommand->setAnswer(VersionAnswer{1,1});
        }
    }
}

} }

