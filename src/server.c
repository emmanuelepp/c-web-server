#include "server.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

int start_server(HTTPServer *server, int port) {
    
    WSADATA wsaDta;

    int result = WSAStartup(MAKEWORD(2,2), &wsaDta);
    if(result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return 1;
    }

    //Create socket
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->sockfd == INVALID_SOCKET) {
        printf("Failed to create socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    // Vinculate the socket
    if (bind(server->sockfd, (struct sockaddr *)&server->address, sizeof(server->address)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(server->sockfd);
        return 1;
    }


    // Listen
    if (listen(server->sockfd, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listin failed with error: %ld\n", WSAGetLastError());
        closesocket(server->sockfd);
        WSACleanup();
        return 1;
    }

    return 0;
}

void stop_server(HTTPServer *server) {
    closesocket(server->sockfd);
    WSACleanup();
}

void serve_forever(HTTPServer *server) {
    printf("Server is running on port %d\n", ntohs(server->address.sin_port));

    while (1) {
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);
        SOCKET client_sock = accept(server->sockfd, (struct sockaddr *)&client_addr, &addrlen);

        if (client_sock == INVALID_SOCKET) {
            printf("Accept failed with error: %ld\n", WSAGetLastError());
            continue;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int recv_size = recv(client_sock, buffer, sizeof(buffer)-1,0);

        if(recv_size == SOCKET_ERROR) {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(client_sock);
            continue;
        }

        printf("Request: %s\n", buffer);

        char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
        send(client_sock, response, strlen(response), 0);

        closesocket(client_sock);

    }
}
