#ifndef IREQUEST_CONTROLLER_H
#define IREQUEST_CONTROLLER_H
#include <string>
#include <engine/IResponse.hpp>
#include <memory>
#include <system/IComponent.hpp>
namespace maycached {
namespace engine {
class IRequestController: public system::IComponent {
public:
    virtual std::string handleRequest(const std::string&) = 0;
};

} }


#endif
