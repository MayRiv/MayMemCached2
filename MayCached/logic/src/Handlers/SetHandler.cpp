#include <Handlers/SetHandler.hpp>
#include <logic/Answers/StatusAnswer.hpp>
#include <logic/Commands/SetCommand.hpp>
#include <iostream>
namespace maycached {
namespace logic {

void SetHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        std::cout << "Set command is received" << std::endl;
        //thowable exception
        auto&& setCommand = dynamic_cast<SetCommand&>(command);

        std::cout << "Succesfully downcasted" << std::endl;
        std::cout << "Key is " << setCommand.getKey() << std::endl;
        std::cout << "Value is " << setCommand.getValue() << std::endl;
        auto success = m_Storage.set(setCommand.getKey(), setCommand.getValue(), setCommand.getExprires());

        setCommand.setAnswer(StatusAnswer{ success ? StatusAnswer::Status::E_SUCCESS
                                                   : StatusAnswer::Status::E_UNKONWN_ERROR});

    }
    else
    {
        pass(command);
    }
}

} }

