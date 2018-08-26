#include <iostream>
#include <connection/IServer.hpp>
#include <connection/ServerFactory.hpp>
#include <engine/IRequestController.hpp>
#include <engine/RequestControllerFactory.hpp>
#include <logic/ILogicController.hpp>
#include <logic/LogicControllerFactory.hpp>
#include <gsl/pointers>
int main()
{
    using namespace maycached;
    logic::LogicControllerFactory lFactory;
    auto logicController = lFactory.buildController();

    engine::RequestControllerFactory eFactory;
    auto requestController = static_cast<std::shared_ptr<maycached::engine::IRequestController>>(
                              eFactory.buildController(static_cast<gsl::not_null<logic::ILogicController*>>(logicController.get())));

    connection::ServerFactory sFactory;
    auto server = sFactory.buildServer(static_cast<gsl::not_null<engine::IRequestController*>>(requestController.get()));

    std::cout << "Hello World!" << std::endl;
    server->run();

    return 0;
}
