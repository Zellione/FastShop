#include "http/http_tcp-server_linux.h"
#include "service/registry.h"
#include <cstring>
#include <unistd.h>

int main(int argc, char* argv[])
{
    service::Registry* registry = new service::Registry();
    registry->init();

    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i],"initdb") == 0)
            {
                registry->getDatabase()->initializeDatabase();
            }
        }

        return 0;
    }

    http::TcpServer server("0.0.0.0", 8080, registry);
    server.startListen();

    if (registry != nullptr)
        delete registry;

    return 0;
}
