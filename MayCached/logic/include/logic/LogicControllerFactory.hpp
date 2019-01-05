#ifndef LOGIC_CONTROLLER_FACTORY_HPP
#define LOGIC_CONTROLLER_FACTORY_HPP
#include <logic/ILogicController.hpp>

#include <memory>
#include <gsl/pointers>
namespace maycached {
namespace system {
    class IMainappStopper;
}
}
namespace maycached {
namespace logic {
class LogicControllerFactory
{
public:
    std::unique_ptr<ILogicController> buildController(gsl::not_null<system::IMainappStopper*> stopper);
};
} }
#endif
