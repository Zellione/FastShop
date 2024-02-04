#include "product_controller.h"
#include "../../../lib/json/include/parser.h"
#include "../model/product.h"
#include "../model/product_list.h"
#include <cstdio>
#include <unistd.h>

namespace shop
{
namespace controller
{
    ProductController::ProductController()
        : router::Controller()
    {
        router::Route* get_action = new router::Route();
        sprintf(get_action->name, "/products");
        get_action->function = [&](const http::HttpRequest* request) { return getAction(request); };
        m_routes->add(get_action);

        router::Route* get_all_action = new router::Route();
        sprintf(get_all_action->name, "/all_products");
        get_all_action->function = [&](const http::HttpRequest* request) { return getAllAction(request); };
        m_routes->add(get_all_action);
    }

    ProductController::~ProductController()
    {
    }

    http::HttpResponse* ProductController::getAction(const http::HttpRequest* request) const
    {
        char cwd[256];
        getcwd(cwd, 256);
        model::Product* product  = new model::Product();
        json::Parser* jsonParser = new json::Parser(std::string(cwd) + "/../../asset/json/product/product.json");
        jsonParser->parse(product);
        delete jsonParser;

        auto response = new http::HttpResponse();
        response->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "application/json")
            ->setBody(product->serialize()->toString(0));

        delete product;
        return response;
    }

    http::HttpResponse* ProductController::getAllAction(const http::HttpRequest* request) const
    {
        char cwd[256];
        getcwd(cwd, 256);
        model::ProductList* productList = new model::ProductList();
        json::Parser* jsonParser = new json::Parser(std::string(cwd) + "/../../asset/json/product/products.json");
        jsonParser->parse(productList);
        delete jsonParser;

        auto response = new http::HttpResponse();
        response->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "application/json")
            ->setBody(productList->serialize()->toString(0));

        return response;
    }
} // namespace controller

} // namespace shop
