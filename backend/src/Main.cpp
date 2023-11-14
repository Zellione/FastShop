#include "../lib/json/include/parser.h"
#include "http/http_tcp-server_linux.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    /* char cwd[256]; */
    /* getcwd(cwd, 256); */
    /* json::Parser* jsonParser = new json::Parser(std::string(cwd) + "/../../asset/json/product/product.json"); */
    /* jsonParser->parse(); */
    /* delete jsonParser; */
    http::TcpServer server("0.0.0.0", 8080);
    server.startListen();

    return 0;
}
