#ifndef STUPID_HANDLER_HPP
#define STUPID_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
namespace maycached {
namespace logic {
class StupidHandler: public  IHandler
{
public:
    StupidHandler(): m_Type(ICommand::CommandType::E_ECHO){}
    void handle(const std::weak_ptr<ICommand>& command) override;

private:
    ICommand::CommandType m_Type;
};

} }
#endif
