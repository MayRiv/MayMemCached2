#ifndef IREQUEST_CONTROLLER_H
#define IREQUEST_CONTROLLER_H
#include <string>
namespace maycached {
namespace engine {
class IRequestController {
public:
    virtual bool handleRequest(std::string) = 0;
};

} }


#endif
