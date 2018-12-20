#include <Handlers/DeleteHandler.hpp>
#include <logic/Answers/StatusAnswer.hpp>
#include <logic/Commands/DeleteCommand.hpp>
#include <iostream>
namespace maycached {
namespace logic {

void DeleteHandler::handle(ICommand &command)
{
    if (command.getType() == m_Type)
    {
        std::cout << "Delete command is received" << std::endl;
        //thowable exception
        auto&& deleteCommand = dynamic_cast<DeleteCommand&>(command);

        std::cout << "Succesfully downcasted" << std::endl;
        std::cout << "Key is " << deleteCommand.getKey() << std::endl;
        auto success = m_Storage.del(deleteCommand.getKey());

        deleteCommand.setAnswer(StatusAnswer{ success ? StatusAnswer::Status::E_SUCCESS
                                                   : StatusAnswer::Status::E_UNKONWN_ERROR});

    }
    else
    {
        pass(command);
    }
}

} }

