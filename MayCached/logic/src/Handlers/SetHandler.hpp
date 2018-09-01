#ifndef SET_HANDLER_HPP
#define SET_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
#include <IStorage.hpp>
namespace maycached {
namespace logic {
class SetHandler: public  IHandler
{
public:
    SetHandler(IStorage& storage): m_Type(ICommand::CommandType::E_SET), m_Storage(storage){}
    void handle(ICommand& command) override;

private:
    ICommand::CommandType m_Type;
    IStorage& m_Storage;
};

} }
#endif
