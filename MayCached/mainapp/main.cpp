#include <iostream>
#include <connection/IServer.hpp>
#include <connection/ServerFactory.hpp>
#include <engine/IRequestController.hpp>
#include <engine/RequestControllerFactory.hpp>
#include <logic/ILogicController.hpp>
#include <logic/LogicControllerFactory.hpp>
#include <gsl/pointers>
#include <SUSDManager.hpp>
int main()
{
    using namespace maycached;
    mainapp::SUSDManager SUSDManager;
    auto stopper = static_cast<gsl::not_null<system::IMainappStopper*>>(&SUSDManager);
    logic::LogicControllerFactory lFactory;
    auto logicController = lFactory.buildController(stopper);

    engine::RequestControllerFactory eFactory;
    auto requestController = eFactory.buildController(static_cast<gsl::not_null<logic::ILogicController*>>(logicController.get()));

    connection::ServerFactory sFactory;
    auto server = sFactory.buildServer(static_cast<gsl::not_null<engine::IRequestController*>>(requestController.get()));

    mainapp::SUSDManager::ComponentsCollection components;

    components[static_cast<uint>(mainapp::InitPriority::E_CONNECTION)] = server.get();
    components[static_cast<uint>(mainapp::InitPriority::E_LOGIC)] = logicController.get();
    components[static_cast<uint>(mainapp::InitPriority::E_ENGINE)] = requestController.get();

    SUSDManager.init(std::move(components));

    SUSDManager.startApplication();

    SUSDManager.suspendCurrentThreadUntilShutdown();
    SUSDManager.stopApplication();
    std::cout << "Application is stopped" << std::endl;
    //server->run();

    return 0;
}
