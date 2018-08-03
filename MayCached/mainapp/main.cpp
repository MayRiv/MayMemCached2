#include <iostream>
#include <connection/IServer.hpp>
#include <connection/ServerFactory.hpp>
#include <engine/IRequestController.hpp>
#include <engine/RequestControllerFactory.hpp>
int main()
{
    maycached::engine::RequestControllerFactory eFactory;
    auto requestController = static_cast<std::shared_ptr<maycached::engine::IRequestController>>(eFactory.buildController());
    maycached::connection::ServerFactory sFactory;
    auto server = sFactory.buildServer(std::weak_ptr<maycached::engine::IRequestController>(requestController));

    std::cout << "Hello World!" << std::endl;
    server->run();

    return 0;
}
