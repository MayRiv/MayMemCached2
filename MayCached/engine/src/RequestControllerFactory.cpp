#include <engine/RequestControllerFactory.hpp>
#include <RequestController.hpp>
#include <engine/IRequestController.hpp>
namespace maycached {
namespace engine {

std::unique_ptr<IRequestController> RequestControllerFactory::buildController(gsl::not_null<logic::ILogicController *> lController)
{
    return std::make_unique<RequestController>(lController);
}

} }
