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
        m_numOfRoutes    = 1;
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
            if (!m_controllers[i]->satisfies(request))
            {
                continue;
            }

            current = m_controllers[i];
            break;
        }
        if (current == 0)
            return responseNotFound();

        return current->routes()->route(request);
    }

    http::HttpResponse* Router::responseNotFound() const
    {
        return (new http::HttpResponse())
            ->setCode(http::Code::NotFound)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->setBody("Cannot find content path");
    }

} // namespace router
} // namespace shop
