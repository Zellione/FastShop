#pragma once

#include "../logging/log.h"
#include "../shop/router/router.h"
#include "database.h"

namespace service
{
    class Registry
    {
      public:
        Registry();
        Registry(const Registry& other) = delete;
        ~Registry();

        void init();

        const logging::Log* getLogger() const;
        const shop::router::Router* getRouter() const;
        const service::Database* getDatabase() const;

      private:
        logging::Log* m_logger;
        shop::router::Router* m_router;
        service::Database* m_database;
    };
} // namespace service
