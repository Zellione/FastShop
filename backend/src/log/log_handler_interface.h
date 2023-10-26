#pragma once

namespace logging
{
    class LogHandler
    {
      public:
        LogHandler(){};
        virtual ~LogHandler(){};
        virtual void log(const int level, const char* message) const = 0;
    };
} // namespace logging
