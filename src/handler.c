#include "handler.h"
#include <stdio.h>
#include <winsock2.h>

void handle_get(HTTPRequest *request, int client_sockfd) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from GET!";
    send(client_sockfd, response, strlen(response),0);

}

void handle_post(HTTPRequest *request, int client_sockfd) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from POST!";
    send(client_sockfd, response, strlen(response),0);

}

void handle_put(HTTPRequest *request, int client_sockfd) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from PUT!";
    send(client_sockfd, response, strlen(response),0);

}

void handle_delete(HTTPRequest *request, int client_sockfd) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from DELETE!";
    send(client_sockfd, response, strlen(response),0);

}