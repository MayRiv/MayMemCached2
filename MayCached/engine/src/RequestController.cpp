#include <RequestController.hpp>
#include <string>
#include <memory>
#include <RequestParser.hpp>
namespace maycached {
namespace engine {
RequestController::RequestController(gsl::not_null<logic::ILogicController *> lController):m_LogicController(lController)
{
    m_Parser = std::make_unique<RequestParser>(); // has to be created by factory using config
}

std::string RequestController::handleRequest(const std::string& input)
{
    const auto failed = "Failed to parse&handle the command: " + input;
    std::string answer{failed};
    if (auto&& command = m_Parser->parseCommand(input))
    {
        m_LogicController->handleCommand(*command);
        answer =  command->getAnswer();
    }

    return answer;
}

void RequestController::start()
{

}

void RequestController::stop()
{

}

} }
