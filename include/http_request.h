#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

typedef enum {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_USPUPPORTED
} HttpMethod;

typedef struct {
    HttpMethod method;
    char *path;
    char *body;
    int content_length;

} HTTPRequest;

HTTPRequest *parse_http_request(const char *raw_request);
void free_http_request(HTTPRequest *request);

#endif