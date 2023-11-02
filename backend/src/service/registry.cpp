#include "registry.h"
#include "../logging/log_handler_console.h"
#include "../shop/controller/base_controller.h"

namespace service
{
Registry::Registry()
    : m_logger(new logging::Log(new logging::LogHandlerConsole(), logging::LogLevel::LOGLEVEL_DEBUG)),
      m_router(new shop::router::Router(new shop::controller::BaseController()))
{
}

Registry::~Registry()
{
    delete m_logger;
    m_logger = 0;

    delete m_router;
    m_router = 0;
}

const logging::Log* Registry::getLogger() const
{
    return m_logger;
}

const shop::router::Router* Registry::getRouter() const
{
    return m_router;
}
} // namespace service
