#pragma once

#include "../router/controller.h"

namespace shop
{
namespace controller
{
    class UserController : public router::Controller
    {
        public:
            UserController();
            UserController(const UserController &other) = delete;
            ~UserController();

        private:

    };
} // namespace controller
} // namespace shop
