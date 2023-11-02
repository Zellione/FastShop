#pragma once

namespace shop
{
namespace router
{
    struct Route
    {
        char name[100];
    };

    class Routes
    {
      public:
        Routes();
        Routes(const Routes& other) = delete;
        ~Routes();

        void add(Route* route);
        bool satisfies(const char* path) const;

      private:
        bool hasEnoughSpace() const;
        void enhance();

      private:
        int m_numOfRoutes;
        int m_maxRoutes;
        Route** m_routes;
    };
} // namespace router
} // namespace shop
