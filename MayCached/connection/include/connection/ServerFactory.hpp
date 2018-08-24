#ifndef SERVERFACTORY_H
#define SERVERFACTORY_H
#include <connection/IServer.hpp>

#include <engine/IRequestController.hpp>
#include <memory>


namespace maycached {
namespace connection {
class ServerFactory {
public:
    std::unique_ptr<IServer> buildServer(std::weak_ptr<engine::IRequestController>);
};

}}
#endif // ISERVERFACTORY_H
