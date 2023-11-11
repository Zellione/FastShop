#include "base_controller.h"
#include "../../../lib/json/include/parser.h"
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
        route->function = [&](const http::HttpRequest* request) { return indexAction(request); };
        m_routes->add(route);
    }

    BaseController::~BaseController()
    {
        std::cout << "BaseController Destructor" << std::endl;
    }

    http::HttpResponse* BaseController::indexAction(const http::HttpRequest* request) const
    {
        json::Parser* jsonParser = new json::Parser("filename.json");
        jsonParser->parse();
        delete jsonParser;

        return (new http::HttpResponse())
            ->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "text/html")
            ->setBody("<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) "
                      "</p></body></html>");
    }
} // namespace controller

} // namespace shop
