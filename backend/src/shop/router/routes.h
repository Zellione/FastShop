#pragma once

#include "../../http/http_request.h"
#include "../../http/http_response.h"
#include <functional>

namespace router
{
class Controller;
}

namespace shop
{
namespace router
{
    struct Route
    {
        char name[100];
        std::function<http::HttpResponse*(const http::HttpRequest*)> function;
    };

    class Routes
    {
      public:
        Routes();
        Routes(const Routes& other) = delete;
        ~Routes();

        void add(Route* route);
        bool satisfies(const http::HttpRequest* request) const;
        http::HttpResponse* route(const http::HttpRequest* request) const;

      private:
        bool hasEnoughSpace() const;
        void enhance();

      private:
        int m_numOfRoutes;
        int m_maxRoutes;
        Route** m_routes;
    };
} // namespace router
} // namespace shop
