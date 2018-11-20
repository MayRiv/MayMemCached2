#ifndef LOGIC_CONTROLLER_HPP
#define LOGIC_CONTROLLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/IHandler.hpp>
#include <memory>
#include <logic/ILogicController.hpp>
#include <IStorage.hpp>
#include <ITimeExpirationManager.hpp>
namespace maycached {
namespace logic {
class LogicController: public ILogicController
{
public:
    LogicController();
    std::unique_ptr<IHandler> buildChainOfHandlers(IStorage& storage/*,config*/);
    void handleCommand(ICommand& command) override;
private:
    std::unique_ptr<IHandler> m_FirstHandler;
    std::unique_ptr<IStorage> m_Storage;
    std::unique_ptr<ITimeExpirationManager> m_TimeExpirationManager;
};
} }
#endif
