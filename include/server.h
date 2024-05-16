#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct {
    int sockfd;
    struct sockaddr_in address;
} HTTPServer;

int start_server(HTTPServer *server, int port);
void stop_server(HTTPServer *server);
void serve_forever(HTTPServer *server);

#endif