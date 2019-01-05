#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include <engine/IRequestController.hpp>
#include <logic/ILogicController.hpp>
#include <IRequestParser.hpp>
namespace maycached {
namespace engine {

class RequestController: public IRequestController {
public:
    RequestController(gsl::not_null<logic::ILogicController*> lController);
    std::string handleRequest(const std::string &) override;

    void start() override;
    void stop() override;
private:
    gsl::not_null<logic::ILogicController*> m_LogicController;
    std::unique_ptr<IRequestParser> m_Parser;
};

} }


#endif
