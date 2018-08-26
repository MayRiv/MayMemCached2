#include <RequestController.hpp>
#include <string>
#include <memory>
#include <SimpleProto/SimpleRequestParser.hpp>
namespace maycached {
namespace engine {
RequestController::RequestController(std::weak_ptr<logic::ILogicController> lController):m_LogicController(lController)
{
    m_Parser = std::make_unique<SimpleRequestParser>(); // has to be created by factory using config
}

std::string RequestController::handleRequest(std::string input)
{
    const auto failed = "Failed to parse&handle the command: " + input;
    std::string answer{failed};
    if (auto&& command = m_Parser->parseCommand(input))
    {
        if (auto&& logic = m_LogicController.lock())
        {
            logic->handleCommand(static_cast<gsl::not_null<logic::ICommand*>>(command.get()));
            answer =  command->getAnswer();
        }
    }

    return answer;
}

} }
