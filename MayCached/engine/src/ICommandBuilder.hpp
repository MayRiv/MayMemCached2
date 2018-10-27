#ifndef I_COMMAND_BUILDER_HPP
#define I_COMMAND_BUILDER_HPP
#include <logic/Commands/GetCommand.hpp>
#include <logic/Commands/SetCommand.hpp>
#include <logic/Commands/ICommand.hpp>
#include <vector>
namespace maycached {
namespace engine {
class ICommandBuilder{
public:
    virtual std::unique_ptr<logic::ICommand> buildGetCommand(const std::vector<std::string>& l) = 0;
    virtual std::unique_ptr<logic::ICommand> buildSetCommand(const std::vector<std::string>& l) = 0;
};
}
}
#endif
