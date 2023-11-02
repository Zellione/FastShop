#pragma once

#include "../logging/log.h"
#include "../shop/router/router.h"

namespace service
{
    class Registry
    {
      public:
        Registry();
        Registry(const Registry& other) = delete;
        ~Registry();

        const logging::Log* getLogger() const;
        const shop::router::Router* getRouter() const;

      private:
        logging::Log* m_logger;
        shop::router::Router* m_router;
    };
} // namespace service
