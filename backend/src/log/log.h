#pragma once

#include "log_handler_interface.h"

namespace logging
{
    enum LogLevel
    {
        LOGLEVEL_ERROR,
        LOGLEVEL_WARN,
        LOGLEVEL_LOG,
        LOGLEVEL_DEBUG
    };

    class Log
    {
      public:
        Log(LogHandler* handler, LogLevel level);
        ~Log();
        Log(Log& other) = delete;

        void error(const char* message) const;
        void warn(const char* message) const;
        void log(const char* message) const;
        void debug(const char* message) const;

      private:
        LogHandler* m_handler;
        LogLevel m_level;
    };
} // namespace logging
