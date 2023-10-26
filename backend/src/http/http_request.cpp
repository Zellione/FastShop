#include "http_request.h"
#include <cstddef>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace http
{
    HttpRequest::HttpRequest(const char* request)
        : m_httpMethod(),
          m_httpProtocol(),
          m_path(),
          m_headers(),
          m_body()
    {
        parseHttpRequest(request);
    }

    HttpRequest::~HttpRequest()
    {
    }

    void HttpRequest::parseHttpRequest(const char* request)
    {
        std::stringstream ss = std::stringstream(request);
        std::string line;

        // Parse first line of request
        std::getline(ss, line);
        int firstOffset = line.find(' ');
        int secondOffset = line.find(' ', firstOffset + 1);
        m_httpMethod = line.substr(0, firstOffset);
        m_path = line.substr(line.find('/'), secondOffset - 4);
        m_httpProtocol = line.substr(secondOffset + 1, line.size() - 7);

        // Collect headers from request
        while (std::getline(ss, line))
        {
            line.erase(line.size() - 1);
            if (line.empty())
                break;

            size_t seperator = line.find(":");
            std::string key = line.substr(0, seperator);
            std::string value = line.substr(seperator + 2, line.size() - key.size() - 2);

            m_headers[key] = value;
        }

        // Collect body from request
        while (std::getline(ss, line))
        {
            m_body += line;
        }
    }

    const std::string* HttpRequest::GetBody() const
    {
        return &m_body;
    }
} // namespace http
