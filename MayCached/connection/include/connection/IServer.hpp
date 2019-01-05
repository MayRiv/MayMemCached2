#ifndef CONNECTION_ISERVER
#define CONNECTION_ISERVER

#include <system/IComponent.hpp>
namespace maycached {
namespace connection {

class IServer: public system::IComponent
{
private:
    virtual void run() = 0;
};


} }
#endif
