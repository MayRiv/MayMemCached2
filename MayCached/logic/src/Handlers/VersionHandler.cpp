#include <Handlers/VersionHandler.hpp>
#include <logic/Answers/VersionAnswer.hpp>
#include <logic/Commands/VersionCommand.hpp>
namespace maycached {
namespace logic {

void VersionHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        auto&& versionCommand = dynamic_cast<VersionCommand&>(command);

        versionCommand.setAnswer(VersionAnswer{1,1});
    }
}

} }

