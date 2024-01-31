#include "product_controller.h"
#include "../../../lib/json/include/parser.h"
#include "../model/product.h"
#include <cstdio>
#include <unistd.h>

namespace shop
{
namespace controller
{
    ProductController::ProductController()
        : router::Controller()
    {
        router::Route* route = new router::Route();
        sprintf(route->name, "/products");
        route->function = [&](const http::HttpRequest* request) { return getAction(request); };
        m_routes->add(route);
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

        auto root = new json::JSONNode(json::JSONNode::Type::OBJECT);
        auto object = new json::JSONObject();
        ((*object)["products"]) = product->serialize();
        root->setObject(object);

        auto response = new http::HttpResponse();
        response->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "application/json")
            ->setBody(root->toString(0));

        delete root;
        delete product;
        return response;
    }
} // namespace controller

} // namespace shop
