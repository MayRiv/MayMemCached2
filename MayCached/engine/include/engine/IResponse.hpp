#ifndef IRESPONSE_HPP
#define IRESPONSE_HPP
#include <string>
namespace maycached {
namespace engine {
class IResponse
{
public:
    virtual std::string toString() const = 0;
};

} }
#endif // IRESPONSE_HPP
