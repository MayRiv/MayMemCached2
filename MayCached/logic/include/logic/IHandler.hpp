#ifndef LOGIC_IHANDLER_HPP
#define LOGIC_IHANDLER_HPP
#include <logic/ICommand.hpp>
#include <memory>
namespace maycached {
namespace logic {
class IHandler
{
    void handle(std::unique_ptr<ICommand> command);
};

} }
#endif
