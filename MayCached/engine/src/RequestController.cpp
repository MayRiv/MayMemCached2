#include <RequestController.hpp>
#include <string>
#include <StupidResponse.hpp>
#include <memory>
namespace maycached {
namespace engine {
RequestController::RequestController()
{

}

std::unique_ptr<IResponse> RequestController::handleRequest(std::string input)
{
    return std::make_unique<StupidResponse>(input);
}

} }
