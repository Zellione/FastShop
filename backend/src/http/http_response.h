#pragma once

#include "http_common.h"
#include <map>
#include <string>

namespace http
{
    class HttpResponse
    {
      public:
        HttpResponse();
        HttpResponse(HttpResponse& other) = delete;
        ~HttpResponse();

        HttpResponse* addHeader(std::string name, std::string value);
        const std::map<std::string, std::string>& getHeaders() const;

        HttpResponse* setCode(Code code);
        Code getCode() const;

        HttpResponse* setBody(std::string body);
        std::string getBody() const;

        HttpResponse* setProtocol(std::string protocol);
        std::string getProtocol() const;

        std::string toString() const;

      private:
        std::string m_protocol;
        Code m_code;
        std::string m_body;
        std::map<std::string, std::string> m_headers;
        std::string stringifyHeaders() const;
    };
} // namespace http
