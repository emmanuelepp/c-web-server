#include "server.h"
#include <stdio.h>

int main() {
    HTTPServer server;
    int port = 8080; 
    
    if (start_server(&server, port) != 0) {
        fprintf(stderr, "Error straring the server! %d\n", port);
        return 1;
    }

    //printf("Servidor iniciado en el puerto %d\n", port);
   
    serve_forever(&server);

    stop_server(&server);
    return 0;
}
