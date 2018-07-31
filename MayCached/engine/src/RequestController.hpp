#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include <engine/IRequestController.hpp>
namespace maycached {
namespace engine {
class RequestController: public IRequestController {
public:
    bool handleRequest(std::string) override;
};

} }


#endif
