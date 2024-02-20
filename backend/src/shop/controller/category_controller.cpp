#include "category_controller.h"
#include <unistd.h>

namespace shop
{
namespace controller
{
    CategoryController::CategoryController()
        : router::Controller()
    {
        router::Route* get_action = new router::Route();
        sprintf(get_action->name, "/categories");
        get_action->function = [&](const http::HttpRequest* request) { return getAction(request); };
        m_routes->add(get_action);
    }

    CategoryController::~CategoryController()
    {
    }

    http::HttpResponse* CategoryController::getAction(const http::HttpRequest* request) const
    {
        char cwd[256];
        getcwd(cwd, 256);
        /* model::Product* product  = new model::Product(); */
        /* json::Parser* jsonParser = new json::Parser(std::string(cwd) + "/../../asset/json/product/product.json"); */
        /* jsonParser->parse(product); */
        /* delete jsonParser; */

        auto response = new http::HttpResponse();
        response->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "application/json")
            /* ->setBody(product->serialize()->toString(0)); */
            ->setBody("");

        /* delete product; */
        return response;
    }

}
}
