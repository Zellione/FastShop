#pragma once

#include "../router/controller.h"

namespace shop
{
namespace controller
{
    class CategoryController : public router::Controller
    {
      public:
        CategoryController();
        CategoryController(const CategoryController& other) = delete;
        ~CategoryController();

        http::HttpResponse* getAction(const http::HttpRequest* request) const;
      private:
    };
} // namespace controller
} // namespace shop
