#include <RequestController.hpp>
#include <string>
#include <StupidResponse.hpp>
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
    std::string answer{"Failed to handle Request"};
    auto command = std::shared_ptr<logic::ICommand>(m_Parser->parseCommand(input));
    if (auto&& logic = m_LogicController.lock())
    {
        logic->handleCommand(command);
        answer =  command->getAnswer();
    }
    return answer;
}

} }
