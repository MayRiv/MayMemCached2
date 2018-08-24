#ifndef LOGIC_CONTROLLER_FACTORY_HPP
#define LOGIC_CONTROLLER_FACTORY_HPP
#include <logic/ILogicController.hpp>
#include <memory>
namespace maycached {
namespace logic {
class LogicControllerFactory
{
public:
    std::unique_ptr<ILogicController> buildController();
};
} }
#endif
