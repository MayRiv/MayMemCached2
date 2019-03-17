#include <LogicController.hpp>
#include <Handlers/StupidHandler.hpp>
#include <Handlers/VersionHandler.hpp>
#include <Handlers/GetHandler.hpp>
#include <Handlers/SetHandler.hpp>
#include <Handlers/DeleteHandler.hpp>
#include <Handlers/ShutdownHandler.hpp>
#include <Storage.hpp>
#include <TimeExpirationManager.hpp>
#include <iostream>
#include <Database/DatabaseManager.hpp>
#include <Database/DataMarshallerRawBinary.hpp>

namespace maycached {
namespace logic {

LogicController::LogicController(gsl::not_null<system::IMainappStopper *> stopper):m_Stopper(stopper)
{
    m_TimeExpirationManager = std::make_unique<TimeExpirationManager>();
    auto DatabaseRawMarshaller = std::make_unique<DataMarshallerRawBinary>();
    m_DatabaseManager = std::make_unique<DatabaseManager>(std::move(DatabaseRawMarshaller));
   
    m_isRunning = false;

}

void LogicController::start()
{
    std::cout << "Start of Logic Controller." << std::endl;
    if (!m_isRunning)
    {
        m_isRunning = true;
        m_Storage = m_DatabaseManager->restoreFromFile(m_TimeExpirationManager.get());
		m_FirstHandler = buildChainOfHandlers(*m_Storage);
        m_TimeExpirationManager->startRepetitivelyRemoveExpired();
    }
}

void LogicController::stop()
{
   if (m_isRunning)
   {
     m_isRunning = false;
     std::cout << "Starting stop of LogicController" <<std::endl;
     m_TimeExpirationManager->stopRepetitivelyRemovingExpired();

     m_DatabaseManager->serializeToFile(*m_Storage);
   }
}
LogicController::~LogicController()
{
    if (m_isRunning)
    {
        m_TimeExpirationManager->stopRepetitivelyRemovingExpired();
    }
}



std::unique_ptr<IHandler> LogicController::buildChainOfHandlers(IStorage& storage)
{
    auto echoHandler = std::make_unique<StupidHandler>();
    auto versionHandler = std::make_unique<VersionHandler>();
    auto setHandler = std::make_unique<SetHandler>(storage);
    auto getHandler = std::make_unique<GetHandler>(storage);
    auto delHandler = std::make_unique<DeleteHandler>(storage);
    auto shutdownHandler = std::make_unique<ShutdownHandler>(m_Stopper);

    echoHandler->addHandlerToChain(std::move(versionHandler));
    echoHandler->addHandlerToChain(std::move(setHandler));
    echoHandler->addHandlerToChain(std::move(getHandler));
    echoHandler->addHandlerToChain(std::move(delHandler));
    echoHandler->addHandlerToChain(std::move(shutdownHandler));

    return echoHandler;
}

void LogicController::handleCommand(ICommand &command)
{
    m_FirstHandler->handle(command);
}

} }
