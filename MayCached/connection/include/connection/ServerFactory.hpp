#ifndef SERVERFACTORY_H
#define SERVERFACTORY_H
#include <connection/IServer.hpp>

#include <engine/IRequestController.hpp>
#include <memory>
#include <gsl/pointers>


namespace maycached {
namespace connection {
class ServerFactory {
public:
    std::unique_ptr<IServer> buildServer(gsl::not_null<engine::IRequestController*>);
};

}}
#endif // ISERVERFACTORY_H
