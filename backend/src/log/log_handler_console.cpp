#include "log_handler_console.h"

namespace logging
{
    LogHandlerConsole::LogHandlerConsole()
    {
    }

    LogHandlerConsole::~LogHandlerConsole()
    {
    }

    void LogHandlerConsole::log(const int level, const char* message) const
    {
        std::cout << message << std::endl;
    }
}
