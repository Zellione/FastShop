#pragma once

#include <map>
#include <regex>
#include <string>

namespace http
{
    class HttpRequest
    {
        public:
            HttpRequest(const char* request);
            ~HttpRequest();

            const std::string* GetBody() const;

        private:
            std::string m_httpMethod;
            std::string m_httpProtocol;
            std::string m_path;
            std::map<std::string, std::string> m_headers;
            std::string m_body;

        private:
            void parseHttpRequest(const char* request);
    };
}
