#include <connection/ServerFactory.hpp>
#include <Server.hpp>
namespace maycached {
namespace connection {

std::unique_ptr<IServer> ServerFactory::buildServer(std::weak_ptr<engine::IRequestController> requestController){
    return std::make_unique<Server>(requestController,7777);
}


} }
