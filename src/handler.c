#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void handle_get(HTTPRequest *request, int client_sockfd) {

    const char *filename = "resources/index.html"; 
    const char *statusMessage = "200 OK";
    int statusCode = 200;  

    if (strcmp(request->path, "/") != 0 && strcmp(request->path, "/index.html") != 0) {
        filename = "resources/error.html";  
        statusMessage = "404 Not Found";
        statusCode = 404;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        const char *errorResponse = "HTTP/1.1 500 Internal Server Error\r\n\r\nServer error.";
        send(client_sockfd, errorResponse, strlen(errorResponse), 0);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(fileSize + 1);

    if (buffer) {
        fread(buffer, 1, fileSize, file);
        buffer[fileSize] = '\0';

        char header[128];
        snprintf(header, sizeof(header), "HTTP/1.1 %s\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n",
                 statusMessage, fileSize);
        send(client_sockfd, header, strlen(header), 0);
        send(client_sockfd, buffer, fileSize, 0);
        free(buffer);
    } else {
        const char *errorResponse = "HTTP/1.1 500 Internal Server Error\r\n\r\nServer error.";
        send(client_sockfd, errorResponse, strlen(errorResponse), 0);
    }

    fclose(file);
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