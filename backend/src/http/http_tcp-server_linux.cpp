#include "http_tcp-server_linux.h"
#include "http_request.h"
#include "http_response.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

namespace http
{
    const int BUFFER_SIZE = 30720;

    TcpServer::TcpServer(std::string ipAddress, int port)
        : m_ipAddress(ipAddress),
          m_port(port),
          m_socket(),
          m_newSocket(),
          m_incomingMessage(),
          m_socketAddress(),
          m_socketAddressLength(sizeof(m_socketAddress)),
          m_registry()
    {
        m_socketAddress.sin_family      = AF_INET;
        m_socketAddress.sin_port        = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());

        if (startServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
            m_registry.getLogger()->error(ss.str().c_str());
            exit(1);
        }
    }

    TcpServer::~TcpServer()
    {
        closeServer();
    }

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            m_registry.getLogger()->error("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr*)&m_socketAddress, m_socketAddressLength) < 0)
        {
            m_registry.getLogger()->error("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_newSocket);
    }

    void TcpServer::startListen()
    {
        if (listen(m_socket, 20) < 0)
        {
            m_registry.getLogger()->error("socket listen failed");
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr)
           << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
        m_registry.getLogger()->log(ss.str().c_str());

        int bytesReceived;
        bool running = true;

        while (running)
        {
            m_registry.getLogger()->log("====== Waiting for a new connection ====== \n\n\n");
            acceptConnection(m_newSocket);

            char buffer[BUFFER_SIZE] = {0};
            bytesReceived            = read(m_newSocket, buffer, BUFFER_SIZE);
            if (bytesReceived < 0)
            {
                m_registry.getLogger()->error("Failed to read bytes from client socket connection");
            }
            http::HttpRequest* request = new http::HttpRequest(buffer);
            m_registry.getLogger()->debug(request->GetBody()->c_str());

            std::ostringstream ss;
            ss << "------ Received request from client ------ \n\n";
            m_registry.getLogger()->log(ss.str().c_str());
            m_registry.getLogger()->debug(buffer);

            http::HttpResponse* response =  m_registry.getRouter()->route(request);
            if (response->hasHeader("Quitting"))
            {
                running = false;
                response->stripHeader("Quitting");
            }
            sendResponse(response);

            delete request;
            delete response;
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
            m_registry.getLogger()->error(ss.str().c_str());
        }
    }

    void TcpServer::sendResponse(http::HttpResponse* response)
    {
        size_t bytesSent;

        std::string responseMessage = response->toString();
        bytesSent = write(m_newSocket, responseMessage.c_str(), responseMessage.size());

        if (bytesSent == responseMessage.size())
        {
            m_registry.getLogger()->log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            m_registry.getLogger()->error("Error sending response to client");
        }
    }
} // namespace http
