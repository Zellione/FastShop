#include "router.h"
#include "controller.h"

#include <cassert>

namespace shop
{
namespace router
{
    Router::Router(Controller* baseRoute)
        : m_numOfRoutes(0),
          m_maxRoutes(10),
          m_controllers(new Controller*[m_maxRoutes])
    {
        m_controllers[0] = baseRoute;
        m_numOfRoutes = 1;
    }

    Router::~Router()
    {
        for (int i = 0; i < m_numOfRoutes; i++)
            delete m_controllers[i];
        delete[] m_controllers;
    }

    http::HttpResponse* Router::route(http::HttpRequest* request) const
    {
        Controller* current = 0;
        for (int i = 0; i < m_numOfRoutes; i++)
        {
            if (!m_controllers[i]->satisfies(request->GetPath()->c_str()))
            {
                continue;
            }

            current = m_controllers[i];
            break;
        }
        assert(current != 0);
        current->routes();
        http::HttpResponse* response = new http::HttpResponse();
        response->setBody(
            "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>");

        return response;
    }
} // namespace router
} // namespace shop
