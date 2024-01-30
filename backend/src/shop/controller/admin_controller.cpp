#include "admin_controller.h"
#include <cstdio>

namespace shop
{
namespace controller
{
    AdminController::AdminController()
        : router::Controller()
    {
        router::Route* route = new router::Route();
        sprintf(route->name, "/quit");
        route->function = [&](const http::HttpRequest* request) { return quitAction(request); };
        m_routes->add(route);
    }

    AdminController::~AdminController()
    {
            std::cout << "AdminController Destructor" << std::endl;
    }

    http::HttpResponse* AdminController::quitAction(const http::HttpRequest* request) const
    {
        return (new http::HttpResponse())
            ->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "text/html")
            ->addHeader("Quitting", "1")
            ->setBody("<!DOCTYPE html><html lang=\"en\"><body><h1> Action </h1><p> Quitting... "
                      "</p></body></html>");
    }
}
} // namespace shop
