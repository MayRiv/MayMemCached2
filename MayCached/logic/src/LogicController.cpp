#include <LogicController.hpp>
#include <Handlers/StupidHandler.hpp>
#include <Handlers/VersionHandler.hpp>
namespace maycached {
namespace logic {

LogicController::LogicController()
{
    m_FirstHandler = buildChainOfHandlers();
}

std::unique_ptr<IHandler> LogicController::buildChainOfHandlers()
{
    auto echoHandler = std::make_unique<StupidHandler>();
    auto versionHandler = std::make_unique<VersionHandler>();

    echoHandler->addHandlerToChain(std::move(versionHandler));

    return echoHandler;
}

void LogicController::handleCommand(const std::weak_ptr<ICommand> &command)
{
    m_FirstHandler->handle(command);
}

} }
