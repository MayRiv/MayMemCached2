#ifndef STATUS_ANSWER_H
#define STATUS_ANSWER_H
#include <string>
namespace maycached {
namespace logic {

struct StatusAnswer
{
    enum class Status
    {
        E_SUCCESS = 0,
        E_UNKONWN_ERROR,
        E_MAX
    };
    Status status;
};

} }
#endif // ECHOANSWER_H
