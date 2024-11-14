#include "HttpServer.h"
#include "Get.h"
#include "Util.h"

HttpServer::HttpServer(int port) : port(port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

void HttpServer::start() {
    std::cout << "Server is running on port " << port << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        handleClient(client_fd);
        close(client_fd);
    }
}

void HttpServer::handleClient(int client_fd) {
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));
    std::string str(buffer);
    std::string response;
    
    //GET方法
    size_t found = str.find("GET");
    if(found == 0){
        response = getResponse(buffer);
    }
    
    //POST方法
    found = str.find("POST");
    if(found == 0){
        response = postResponse(buffer);
    }

    //PUT方法
    found = str.find("PUT");
    if(found == 0){
        response = putResponse(buffer);
    }
    //DELETE方法
    found = str.find("DELETE");
    if(found == 0){
        response = deleteResponse(buffer);
    }
    send(client_fd, response.c_str(), response.size(), 0);
}

std::string HttpServer::getResponse(const std::string& request) {
    std::string response;
    response = Get::getResponse(request);
    return response;
}

std::string HttpServer::postResponse(const std::string& request) {
    std::string response;
    response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: 13\r\n";
    response += "\r\n";
    response += "Hello, POST!";
    return response;
}

std::string HttpServer::putResponse(const std::string& request) {
    std::string response;
    response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: 13\r\n";
    response += "\r\n";
    response += "Hello, PUT!";
    return response;
}

std::string HttpServer::deleteResponse(const std::string& request) {
    std::string response;
    response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: 13\r\n";
    response += "\r\n";
    response += "Hello, DELETE!";
    return response;
}
