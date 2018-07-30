#ifndef CONNECTION_ISERVER
#define CONNECTION_ISERVER
namespace maycached {
namespace connection {

class IServer
{
public:
    virtual void run() = 0;
};


} }
#endif
