#ifndef IREQUEST_CONTROLLER_H
#define IREQUEST_CONTROLLER_H
#include <string>
#include <engine/IResponse.hpp>
#include <memory>
namespace maycached {
namespace engine {
class IRequestController {
public:
    virtual std::string handleRequest(std::string) = 0;
};

} }


#endif
