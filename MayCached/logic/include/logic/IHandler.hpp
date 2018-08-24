#ifndef LOGIC_IHANDLER_HPP
#define LOGIC_IHANDLER_HPP
#include <logic/Commands/ICommand.hpp>
#include <memory>
namespace maycached {
namespace logic {
class IHandler
{
    std::unique_ptr<IHandler> m_NextHandler{nullptr};
public:
    virtual void handle(const std::weak_ptr<ICommand>& command) = 0;
    void setNextHandler(std::unique_ptr<IHandler>&& handler)
    {
        m_NextHandler = std::move(handler);
    }
    template <class T>
    void addHandlerToChain(T&& handler)
    {
        if (m_NextHandler)
        {
            m_NextHandler->addHandlerToChain(std::forward<T>(handler));
        }
        else
        {
            setNextHandler(std::forward<T>(handler));
        }
    }
};

} }
#endif
