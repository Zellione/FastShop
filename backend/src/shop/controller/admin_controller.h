#pragma once

#include "../router/controller.h"

namespace shop
{
namespace controller
{
    class AdminController : public router::Controller
    {
      public:
        AdminController();
        AdminController(const AdminController& other) = delete;
        ~AdminController();

        http::HttpResponse* quitAction(const http::HttpRequest* request) const;
      private:
    };
} // namespace controller
} // namespace shop
