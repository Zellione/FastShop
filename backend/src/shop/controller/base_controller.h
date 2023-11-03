#pragma once

#include "../router/controller.h"

namespace shop
{
namespace controller
{
    class BaseController : public router::Controller
    {
      public:
        BaseController();
        BaseController(const BaseController& other) = delete;
        ~BaseController();

        http::HttpResponse* indexAction(const http::HttpRequest* request) const;

      private:
    };
} // namespace controller
} // namespace shop
