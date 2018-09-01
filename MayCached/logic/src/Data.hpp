#ifndef DATA_HPP
#define DATA_HPP
#include <chrono>
#include <optional>
namespace maycached {
namespace logic {
struct Data
{
    std::string key;
    std::string value;
    std::optional<std::chrono::time_point<std::chrono::system_clock>> willBeExpired = std::nullopt;
};

} }
#endif
