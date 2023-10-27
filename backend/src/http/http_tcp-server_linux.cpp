#include "http_tcp-server_linux.h"
#include "http_common.h"
#include "http_request.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

#include "../log/log_handler_console.h"
#include "http_response.h"

namespace
{
    const int BUFFER_SIZE = 30720;

    /* void dolog(const std::string& message) */
    /* { */
    /*     std::cout << message << std::endl; */
    /* } */

    /* void exitWithError(const std::string& errorMessage) */
    /* { */
    /*     dolog("ERROR: " + errorMessage); */
    /*     exit(1); */
    /* } */
} // namespace

namespace http
{
    TcpServer::TcpServer(std::string ipAddress, int port)
        : m_ipAddress(ipAddress),
          m_port(port),
          m_socket(),
          m_newSocket(),
          m_incomingMessage(),
          m_socketAddress(),
          m_socketAddressLength(sizeof(m_socketAddress)),
          m_serverMessage(buildResponse()),
          m_logger(new logging::Log(new logging::LogHandlerConsole(), logging::LOGLEVEL_DEBUG))
    {
        m_socketAddress.sin_family      = AF_INET;
        m_socketAddress.sin_port        = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());

        if (startServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
            m_logger->error(ss.str().c_str());
        }
    }

    TcpServer::~TcpServer()
    {
        closeServer();
        delete m_logger;
        m_logger = 0;
    }

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            m_logger->error("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr*)&m_socketAddress, m_socketAddressLength) < 0)
        {
            m_logger->error("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    std::string TcpServer::buildResponse()
    {
        http::HttpResponse response;
        std::string htmlFile =
            "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
        response.setBody(htmlFile)
            ->setCode(http::Code::OK)
            ->setProtocol(http::HTTP_VERSION_1_1)
            ->addHeader("Content-Type", "text/html");
        /* std::ostringstream ss; */
        /* ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n" << htmlFile;
         */

        return response.toString();
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_newSocket);
        exit(0);
    }

    void TcpServer::startListen()
    {
        if (listen(m_socket, 20) < 0)
        {
            m_logger->error("socket listen failed");
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr)
           << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
        m_logger->log(ss.str().c_str());

        int bytesReceived;

        while (true)
        {
            m_logger->log("====== Waiting for a new connection ====== \n\n\n");
            acceptConnection(m_newSocket);

            char buffer[BUFFER_SIZE] = {0};
            bytesReceived            = read(m_newSocket, buffer, BUFFER_SIZE);
            if (bytesReceived < 0)
            {
                m_logger->error("Failed to read bytes from client  socket connection");
            }
            http::HttpRequest request = http::HttpRequest(buffer);
            m_logger->debug(request.GetBody()->c_str());

            std::ostringstream ss;
            ss << "------ Received request from client ------ \n\n";
            m_logger->log(ss.str().c_str());
            m_logger->debug(buffer);

            sendResponse();

            close(m_newSocket);
        }
    }

    void TcpServer::acceptConnection(int& newSocket)
    {
        newSocket = accept(m_socket, (sockaddr*)&m_socketAddress, &m_socketAddressLength);
        if (newSocket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr)
               << "; PORT: " << ntohs(m_socketAddress.sin_port);
            m_logger->error(ss.str().c_str());
        }
    }

    void TcpServer::sendResponse()
    {
        size_t bytesSent;

        bytesSent = write(m_newSocket, m_serverMessage.c_str(), m_serverMessage.size());

        if (bytesSent == m_serverMessage.size())
        {
            m_logger->log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            m_logger->error("Error sending response to client");
        }
    }
} // namespace http
