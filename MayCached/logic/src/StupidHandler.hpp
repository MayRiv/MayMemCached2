#ifndef LOGIC_HANDLER_HPP
#define LOGIC_HANDLER_HPP
#include <logic/IHandler.hpp>

namespace maycached {
namespace logic {
class StupidHandler: public  IHandler
{
    void handle(std::unique_ptr<ICommand> command);
};

} }
#endif
