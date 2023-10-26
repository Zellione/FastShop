#pragma once

#include "../log/log.h"
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
        std::string m_serverMessage;
        logging::Log* m_logger;

      private:
        int startServer();
        void closeServer();
        std::string buildResponse();
        void acceptConnection(int& newSocket);
        void sendResponse();
    };
} // namespace http
