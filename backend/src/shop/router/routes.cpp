#include "routes.h"
#include <cassert>
#include <cstring>

namespace shop
{
namespace router
{
    Routes::Routes()
        : m_numOfRoutes(0),
          m_maxRoutes(5),
          m_routes(new Route*[m_maxRoutes])
    {
    }

    Routes::~Routes()
    {
        for (int i = 0; i < m_numOfRoutes; i++)
            delete m_routes[i];
        delete[] m_routes;
    }

    void Routes::add(Route* route)
    {
        if (!hasEnoughSpace())
            enhance();

        m_routes[m_numOfRoutes] = route;
        m_numOfRoutes++;
    }

    bool Routes::satisfies(const http::HttpRequest* request) const
    {
        for (int i = 0; i < m_numOfRoutes; i++)
        {
            if (strcmp(m_routes[i]->name, request->GetPath()->c_str()) == 0)
                return true;
        }

        return false;
    }

    http::HttpResponse* Routes::route(const http::HttpRequest* request) const
    {
        http::HttpResponse* response = 0;
        for (int i = 0; i < m_numOfRoutes; i++)
        {
            if (strcmp(m_routes[i]->name, request->GetPath()->c_str()) == 0)
            {
                response =  m_routes[i]->function(request);
            }
        }

        assert(response != 0);

        return response;
    }

    bool Routes::hasEnoughSpace() const
    {
        return m_numOfRoutes > m_maxRoutes - 2;
    }

    void Routes::enhance()
    {
        Route** temp = new Route*[m_maxRoutes];
        for (int i = 0; i < m_maxRoutes; i++)
            temp[i] = m_routes[i];
        delete[] m_routes;
        m_routes = new Route*[m_maxRoutes + 5];
        for (int i = 0; i < m_maxRoutes; i++)
            m_routes[i] = temp[i];
        delete[] temp;
        m_maxRoutes += 5;
    }
} // namespace router
} // namespace shop
