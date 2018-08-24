#include <engine/RequestControllerFactory.hpp>
#include <RequestController.hpp>
#include <engine/IRequestController.hpp>
namespace maycached {
namespace engine {

std::unique_ptr<IRequestController> RequestControllerFactory::buildController(std::weak_ptr<logic::ILogicController> lController)
{
    return std::make_unique<RequestController>(lController);
}

} }
