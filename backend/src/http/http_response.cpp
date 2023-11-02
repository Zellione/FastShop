#include "http_response.h"
#include "http_common.h"
#include <sstream>

namespace http
{
    HttpResponse::HttpResponse()
        : m_protocol(http::HTTP_VERSION_1_1),
          m_code(Code::OK),
          m_body(),
          m_headers()
    {
        addHeader("Content-Type", "text/html");
    }

    HttpResponse::~HttpResponse()
    {
    }

    HttpResponse* HttpResponse::addHeader(std::string name, std::string value)
    {
        m_headers[name] = value;

        return this;
    }

    const std::map<std::string, std::string>& HttpResponse::getHeaders() const
    {
        return m_headers;
    }

    HttpResponse* HttpResponse::setCode(Code code)
    {
        m_code = code;

        return this;
    }

    Code HttpResponse::getCode() const
    {
        return m_code;
    }

    HttpResponse* HttpResponse::setBody(std::string body)
    {
        m_body                      = body;
        m_headers["Content-Length"] = std::to_string(m_body.size());

        return this;
    }

    std::string HttpResponse::getBody() const
    {
        return m_body;
    }

    HttpResponse* HttpResponse::setProtocol(std::string protocol)
    {
        m_protocol = protocol;

        return this;
    }

    std::string HttpResponse::getProtocol() const
    {
        return m_protocol;
    }

    std::string HttpResponse::toString() const
    {
        std::ostringstream ss;
        ss << m_protocol << " " << http::codetoInt(m_code) << " " << http::reasonPhrase(m_code) << "\n";
        ss << stringifyHeaders();
        ss << "\n";
        ss << m_body;

        return ss.str();
    }

    std::string HttpResponse::stringifyHeaders() const
    {
        std::ostringstream ss;
        for (auto const& header : m_headers)
        {
            ss << header.first << ": " << header.second << "\n";
        }

        return ss.str();
    }
} // namespace http
