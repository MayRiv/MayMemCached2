#include <Handlers/GetHandler.hpp>
#include <logic/Answers/GetAnswer.hpp>
#include <logic/Commands/GetCommand.hpp>
namespace maycached {
namespace logic {

void GetHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        auto&& getCommand = dynamic_cast<GetCommand&>(command);

        auto&& result = m_Storage.get(getCommand.getKey());
        getCommand.setAnswer(GetAnswer{result});

    }
    else
    {
        pass(command);
    }
}

} }

