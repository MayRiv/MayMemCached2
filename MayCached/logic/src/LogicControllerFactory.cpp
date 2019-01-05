#include <logic/LogicControllerFactory.hpp>
#include <LogicController.hpp>
#include <system/IMainappStopper.hpp>
namespace maycached {
namespace logic {

std::unique_ptr<ILogicController> LogicControllerFactory::buildController(gsl::not_null<system::IMainappStopper*> stopper)
{
    return std::make_unique<LogicController>(stopper);
}

} }
