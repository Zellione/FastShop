#pragma once

#include "routes.h"
#include <iostream>

namespace shop
{
namespace router
{
    class Controller
    {
      public:
        Controller()
            : m_routes(new Routes()){};
        Controller(const Controller& other) = delete;

        virtual ~Controller()
        {
            std::cout << "Controller Destructor" << std::endl;
            delete m_routes;
        };

        virtual bool satisfies(const char* route)
        {
            return m_routes->satisfies(route);
        };

        const Routes* routes()
        {
            return m_routes;
        }

      protected:
        void addRoute(Route* route)
        {
            m_routes->add(route);
        }

      protected:
        Routes* m_routes;
    };
} // namespace router

} // namespace shop
