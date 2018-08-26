#ifndef LOGIC_CONTROLLER_HPP
#define LOGIC_CONTROLLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <logic/IHandler.hpp>
#include <memory>
#include <logic/ILogicController.hpp>
namespace maycached {
namespace logic {
class LogicController: public ILogicController
{
public:
    LogicController();
    std::unique_ptr<IHandler> buildChainOfHandlers(/*config*/);
    void handleCommand(const gsl::not_null<ICommand *> command) override;
private:
    std::unique_ptr<IHandler> m_FirstHandler;
};
} }
#endif
