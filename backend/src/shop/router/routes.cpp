#include "routes.h"
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

    bool Routes::satisfies(const char* path) const
    {
        for (int i = 0; i < m_numOfRoutes; i++)
        {
            if (strcmp(m_routes[i]->name, path) == 0)
                return true;
        }

        return false;
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
