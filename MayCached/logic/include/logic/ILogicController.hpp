#ifndef ILOGIC_CONTROLLER_HPP
#define ILOGIC_CONTROLLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <memory>
namespace maycached {
namespace logic {
class ILogicController
{
public:
    virtual void handleCommand(const gsl::not_null<ICommand*> command) = 0;
};
} }
#endif
