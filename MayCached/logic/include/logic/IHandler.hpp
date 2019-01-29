#ifndef LOGIC_IHANDLER_HPP
#define LOGIC_IHANDLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <memory>
#include <gsl/pointers>
namespace maycached {
namespace logic {
class IHandler
{
    std::unique_ptr<IHandler> m_NextHandler{nullptr};
public:
    virtual void handle(ICommand& command) = 0;

    void addHandlerToChain(std::unique_ptr<IHandler>&& handler)
    {
        if (m_NextHandler)
        {
            m_NextHandler->addHandlerToChain(std::move(handler));
        }
        else
        {
            m_NextHandler = std::move(handler);
        }
    }
protected:
    void pass(ICommand& command){
        if (m_NextHandler)
        {
            m_NextHandler->handle(command);
        }
    }
};

} }
#endif
