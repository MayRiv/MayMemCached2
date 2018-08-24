#include <logic/LogicControllerFactory.hpp>
#include <LogicController.hpp>
namespace maycached {
namespace logic {

std::unique_ptr<ILogicController> LogicControllerFactory::buildController()
{
    return std::make_unique<LogicController>();
}

} }
