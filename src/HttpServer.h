#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

class HttpServer {
public:
    HttpServer(int port);
    void start();

private:
    int server_fd;
    int port;
    void handleClient(int client_fd);
    std::string getResponse(const std::string& request);
    std::string postResponse(const std::string& request);
    std::string putResponse(const std::string& request);
    std::string deleteResponse(const std::string& request);
};
