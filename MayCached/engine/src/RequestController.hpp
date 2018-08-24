#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include <engine/IRequestController.hpp>
#include <logic/ILogicController.hpp>
#include <IRequestParser.hpp>
namespace maycached {
namespace engine {

class RequestController: public IRequestController {
public:
    RequestController(std::weak_ptr<logic::ILogicController> lController);
    std::string handleRequest(std::string) override;
private:
    std::weak_ptr<logic::ILogicController> m_LogicController;
    std::unique_ptr<IRequestParser> m_Parser;
};

} }


#endif
