#include "http/http_tcp-server_linux.h"

int main(int argc, char* argv[])
{
    http::TcpServer server("0.0.0.0", 8080);
    server.startListen();

    return 0;
}
