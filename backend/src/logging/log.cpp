#include "log.h"
#include "log_handler_interface.h"
#include <functional>
#include <iostream>

namespace logging
{
    Log::Log(LogHandler* handler, LogLevel level)
        : m_handler(handler),
          m_level(level)
    {
    }

    Log::~Log()
    {
        delete m_handler;
        m_handler = 0;
    }

    void Log::error(const char* message) const
    {
        if (m_level < LOGLEVEL_ERROR)
            return;

        m_handler->log(LOGLEVEL_ERROR, message);
    }

    void Log::warn(const char* message) const
    {
        if (m_level < LOGLEVEL_WARN)
            return;

        m_handler->log(LOGLEVEL_WARN, message);
    }

    void Log::log(const char* message) const
    {
        if (m_level < LOGLEVEL_LOG)
            return;

        m_handler->log(LOGLEVEL_LOG, message);
    }

    void Log::debug(const char* message) const
    {
        if (m_level < LOGLEVEL_DEBUG)
            return;

        m_handler->log(LOGLEVEL_DEBUG, message);
    }

    void Log::changeLogLevel(LogLevel level)
    {
        m_level = level;
    }

} // namespace log
