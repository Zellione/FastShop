#pragma once

#include "../router/controller.h"

namespace shop
{
namespace controller
{
    class ProductController : public router::Controller
    {
      public:
        ProductController();
        ProductController(const ProductController& other) = delete;
        ~ProductController();

        http::HttpResponse* getAction(const http::HttpRequest* request) const;
        http::HttpResponse* getAllAction(const http::HttpRequest* request) const;

      private:
    };
} // namespace controller
} // namespace shop
