#include "registry.h"
#include "../logging/log_handler_console.h"
#include "../shop/controller/base_controller.h"
#include "../shop/model/product.h"
#include "database.h"

namespace service
{
Registry::Registry()
    : m_logger(new logging::Log(new logging::LogHandlerConsole(), logging::LogLevel::LOGLEVEL_DEBUG)),
      m_router(new shop::router::Router(new shop::controller::BaseController())),
      m_database(new service::Database(m_logger))
{
}

Registry::~Registry()
{
    delete m_logger;
    m_logger = 0;

    delete m_router;
    m_router = 0;

    delete m_database;
    m_database = 0;
}

void Registry::init()
{
    m_database->addModel(new shop::model::Product);
}

const logging::Log* Registry::getLogger() const
{
    return m_logger;
}

const shop::router::Router* Registry::getRouter() const
{
    return m_router;
}

const service::Database* Registry::getDatabase() const
{
    return m_database;
}
} // namespace service
