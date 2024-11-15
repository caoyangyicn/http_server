#include "HttpServer.h"

int main(int argc, char* argv[]) {
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    int port = std::stoi(argv[1]);
    HttpServer server(port);
    server.start();
    return 0;
}