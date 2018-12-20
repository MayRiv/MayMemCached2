#ifndef DELETE_HANDLER_HPP
#define DELETE_HANDLER_HPP
#include <logic/IHandler.hpp>
#include <logic/Commands/ICommand.hpp>
#include <IStorage.hpp>
namespace maycached {
namespace logic {
class DeleteHandler: public  IHandler
{
public:
    DeleteHandler(IStorage& storage): m_Type(ICommand::CommandType::E_DELETE), m_Storage(storage){}
    void handle(ICommand& command) override;

private:
    ICommand::CommandType m_Type;
    IStorage& m_Storage;
};

} }
#endif
