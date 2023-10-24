#pragma once

#include "log_handler_interface.h"
#include <iostream>

namespace logging
{
    class LogHandlerConsole : public LogHandler
    {
        public:
            LogHandlerConsole();
            ~LogHandlerConsole() override;
            LogHandlerConsole(LogHandlerConsole &other) = delete;

            void log(const int level, const char* message) const override;
    };
}
