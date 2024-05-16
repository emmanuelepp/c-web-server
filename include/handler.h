#ifndef HANDLER_H
#define HANDLER_H

#include "http_request.h"

void handle_get(HTTPRequest *request, int client_sockfd);
void handle_post(HTTPRequest *request, int client_sockfd);
void handle_put(HTTPRequest *request, int client_sockfd);
void handle_delete(HTTPRequest *request, int client_sockfd);

#endif