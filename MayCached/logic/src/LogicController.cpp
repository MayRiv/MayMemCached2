#include <LogicController.hpp>
#include <Handlers/StupidHandler.hpp>
#include <Handlers/VersionHandler.hpp>
#include <Handlers/GetHandler.hpp>
#include <Handlers/SetHandler.hpp>
#include <Storage.hpp>
namespace maycached {
namespace logic {

LogicController::LogicController()
{
    m_Storage = std::make_unique<Storage>();
    m_FirstHandler = buildChainOfHandlers(*m_Storage);

}

std::unique_ptr<IHandler> LogicController::buildChainOfHandlers(IStorage& storage)
{
    auto echoHandler = std::make_unique<StupidHandler>();
    auto versionHandler = std::make_unique<VersionHandler>();
    auto setHandler = std::make_unique<GetHandler>(storage);
    auto getHandler = std::make_unique<SetHandler>(storage);

    echoHandler->addHandlerToChain(std::move(versionHandler));
    echoHandler->addHandlerToChain(std::move(setHandler));
    echoHandler->addHandlerToChain(std::move(getHandler));

    return echoHandler;
}

void LogicController::handleCommand(ICommand &command)
{
    m_FirstHandler->handle(command);
}

} }
