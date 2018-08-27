#ifndef VERSION_HANDLER_HPP
#define VERSION_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
namespace maycached {
namespace logic {
class VersionHandler: public  IHandler
{
public:
    VersionHandler(): m_Type(ICommand::CommandType::E_VERSION){}
    void handle(ICommand& command) override;

private:
    ICommand::CommandType m_Type;
};

} }
#endif
