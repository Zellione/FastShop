#pragma once

#include "../service/registry.h"
#include "http_response.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>

namespace http
{
    class TcpServer
    {
      public:
        TcpServer(std::string ipAddress, int port);
        TcpServer(const TcpServer& other) = delete;
        ~TcpServer();
        void startListen();

      private:
        std::string m_ipAddress;
        int m_port;
        int m_socket;
        int m_newSocket;
        long m_incomingMessage;
        sockaddr_in m_socketAddress;
        unsigned int m_socketAddressLength;

        service::Registry m_registry;

      private:
        int startServer();
        void closeServer();
        void acceptConnection(int& newSocket);
        void sendResponse(http::HttpResponse* response);
    };
} // namespace http
