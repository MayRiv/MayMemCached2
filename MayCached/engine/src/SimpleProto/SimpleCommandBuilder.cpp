#include <SimpleProto/SimpleCommandBuilder.hpp>
#include <logic/Commands/SetCommand.hpp>
#include <logic/Commands/GetCommand.hpp>
#include <logic/Commands/DeleteCommand.hpp>
#include <SimpleProto/Representations/SimpleGetRepresentation.hpp>
#include <SimpleProto/Representations/SimpleStatusRepresentation.hpp>
#include <string>
#include <optional>
#include <iostream>
namespace maycached {
namespace engine {
std::unique_ptr<logic::ICommand> SimpleCommandBuilder::buildGetCommand(const std::vector<std::string> &l)
{
    auto getRep = std::make_unique<SimpleGetRepresentation>();
    auto getCom = std::make_unique<logic::GetCommand>(std::move(getRep), l[1]);
    std::cout << "Get command is built" << std::endl;
    return getCom;
}

std::unique_ptr<logic::ICommand> SimpleCommandBuilder::buildSetCommand(const std::vector<std::string> &l)
{
    auto setRep = std::make_unique<SimpleStatusRepresentation>();
    std::optional<uint32_t> expireTime  = std::nullopt;
    if (l.size() == 4)
    {
        expireTime = std::stoi(l[3]);
    }
    auto setCom = std::make_unique<logic::SetCommand>(std::move(setRep), l[1], l[2], expireTime);
        std::cout << "Set command is built" << std::endl;
    return setCom;
}
std::unique_ptr<logic::ICommand> SimpleCommandBuilder::buildDelCommand(const std::vector<std::string> &l)
{
    auto delRep = std::make_unique<SimpleStatusRepresentation>();
    auto deltCom = std::make_unique<logic::DeleteCommand>(std::move(delRep), l[1]);
    std::cout << "Delete command is built" << std::endl;
    return deltCom;
}


}
}
