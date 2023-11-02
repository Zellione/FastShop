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
            BaseController(const BaseController &other) = delete;
            ~BaseController();

        private:

    };
} // namespace controller
} // namespace shop
