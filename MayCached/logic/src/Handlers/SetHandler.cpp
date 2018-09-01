#include <Handlers/SetHandler.hpp>
#include <logic/Answers/StatusAnswer.hpp>
#include <logic/Commands/SetCommand.hpp>
namespace maycached {
namespace logic {

void SetHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        //thowable exception
        auto&& setCommand = dynamic_cast<SetCommand&>(command);

        auto success = m_Storage.set(setCommand.getKey(), setCommand.getValue(), setCommand.getExprires());

        setCommand.setAnswer(StatusAnswer{ success ? StatusAnswer::Status::E_SUCCESS
                                                   : StatusAnswer::Status::E_UNKONWN_ERROR});

    }
}

} }

