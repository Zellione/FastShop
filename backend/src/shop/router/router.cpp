#include "router.h"
#include "../controller/admin_controller.h"
#include "../controller/user_controller.h"
#include "../controller/product_controller.h"
#include "../controller/category_controller.h"

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

        registerRoutes();
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

    void Router::registerRoute(Controller* controller)
    {
        if (m_numOfRoutes < m_maxRoutes)
        {
            m_controllers[m_numOfRoutes] = controller;
            m_numOfRoutes++;
        }
    }

    void Router::registerRoutes()
    {
        registerRoute(new controller::UserController());
        registerRoute(new controller::AdminController());
        registerRoute(new controller::ProductController());
        registerRoute(new controller::CategoryController());
    }

} // namespace router
} // namespace shop
