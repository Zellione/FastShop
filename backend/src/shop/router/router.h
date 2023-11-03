#pragma once

#include "../../http/http_request.h"
#include "../../http/http_response.h"
#include "controller.h"

namespace shop
{
namespace router
{
    class Router
    {
      public:
        Router(Controller* baseRoute);
        Router(const Router& other) = delete;
        ~Router();

        http::HttpResponse* route(http::HttpRequest* request) const;

      private:
        http::HttpResponse* responseNotFound() const;

      private:
        int m_numOfRoutes;
        int m_maxRoutes;
        Controller** m_controllers;
    };
} // namespace router
} // namespace shop
