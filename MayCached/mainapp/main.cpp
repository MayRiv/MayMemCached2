#include <iostream>
#include <connection/IServer.hpp>
#include <connection/ServerFactory.hpp>
#include <engine/IRequestController.hpp>
#include <engine/RequestControllerFactory.hpp>
#include <logic/ILogicController.hpp>
#include <logic/LogicControllerFactory.hpp>
int main()
{
    maycached::logic::LogicControllerFactory lFactory;
    auto logicController = static_cast<std::shared_ptr<maycached::logic::ILogicController>>(lFactory.buildController());

    maycached::engine::RequestControllerFactory eFactory;
    auto requestController = static_cast<std::shared_ptr<maycached::engine::IRequestController>>(
                              eFactory.buildController(std::weak_ptr<maycached::logic::ILogicController>(logicController)));

    maycached::connection::ServerFactory sFactory;
    auto server = sFactory.buildServer(std::weak_ptr<maycached::engine::IRequestController>(requestController));

    std::cout << "Hello World!" << std::endl;
    server->run();

    return 0;
}
