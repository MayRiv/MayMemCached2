#ifndef ILOGIC_CONTROLLER_HPP
#define ILOGIC_CONTROLLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <memory>
#include <system/IComponent.hpp>
namespace maycached {
namespace logic {
class ILogicController: public system::IComponent
{
public:
    ILogicController():system::IComponent()
    {}
    virtual void handleCommand(ICommand& command) = 0;
    virtual ~ILogicController() = default;
};
} }
#endif
