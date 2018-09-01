#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
#include <IStorage.hpp>
namespace maycached {
namespace logic {
class GetHandler: public  IHandler
{
public:
    GetHandler(IStorage& storage): m_Type(ICommand::CommandType::E_GET), m_Storage(storage){}
    void handle(ICommand& command) override;

private:
    ICommand::CommandType m_Type;
    IStorage& m_Storage;
};

} }
#endif
