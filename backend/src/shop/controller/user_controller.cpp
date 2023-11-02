#include "user_controller.h"
#include <cstdio>

namespace shop
{
namespace controller
{
    UserController::UserController()
        : router::Controller()
    {
        router::Route* route = new router::Route();
        sprintf(route->name, "/i/am/a/test/route");
        m_routes->add(route);
    }

    UserController::~UserController()
    {
            std::cout << "UserController Destructor" << std::endl;
    }

} // namespace controller

} // namespace shop
