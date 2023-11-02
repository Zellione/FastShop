#include "base_controller.h"
#include <cstdio>

namespace shop
{
namespace controller
{
    BaseController::BaseController()
        : router::Controller()
    {
        router::Route* route = new router::Route();
        sprintf(route->name, "/");
        m_routes->add(route);
    }

    BaseController::~BaseController()
    {
            std::cout << "BaseController Destructor" << std::endl;
    }

} // namespace controller

} // namespace shop
