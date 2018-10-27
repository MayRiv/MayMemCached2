#ifndef SIMPLE_COMMAND_BUILDER_HPP
#define SIMPLE_COMMAND_BUILDER_HPP
#include <logic/Commands/GetCommand.hpp>
#include <ICommandBuilder.hpp>
#include <vector>
namespace maycached {
namespace engine {
class SimpleCommandBuilder : public ICommandBuilder {
public:
    std::unique_ptr<logic::ICommand> buildGetCommand(const std::vector<std::string>& l) override;
    std::unique_ptr<logic::ICommand> buildSetCommand(const std::vector<std::string> &l) override;
};
}
}
#endif
