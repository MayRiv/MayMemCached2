#ifndef REQUESTCONTROLLERFACTORY_HPP
#define REQUESTCONTROLLERFACTORY_HPP

#include <memory>
#include <engine/IRequestController.hpp>
#include <logic/ILogicController.hpp>
namespace maycached {
namespace engine {

class RequestControllerFactory
{
public:
    std::unique_ptr<IRequestController> buildController(std::weak_ptr<logic::ILogicController>);
};
} }
#endif // REQUESTCONTROLLERFACTORY_HPP
