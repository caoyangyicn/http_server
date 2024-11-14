#include "Get.h"
#include "Util.h"


const std::vector<std::string> IMGLIST = {".jpg", ".jpeg", ".png", ".gif", ".bmp", ".ico"};

std::pair<int, std::string> Get::getContent(std::string path) {
    std::string content;
    int length = 0;

    if (path == "/") {
        content = "Hello, GET!";
        length = content.size();
    } else {
        std::ifstream file("../web/html/" + path); // Assuming the path is relative to the current directory
        if (!file.is_open()) {
            file.open("../web/html/404.html");            
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        length = content.size();
        file.close();
    }
    return std::make_pair(length, content);
}

std::string Get::getResponse(std::string request) {
    // 解析请求并获取路径
    std::vector<std::string> requestLines = Util::StringToVecByEnter(request);
    std::string path = "/";
    if (!requestLines.empty()) {
        std::vector<std::string> requestLineParts = Util::StringToVecBySpace(requestLines[0]);
        if (requestLineParts.size() > 1) {
            path = requestLineParts[1];
        }
    }

    // 获取内容
    std::pair<int, std::string> content = Get::getContent(path);

    // HTML
    if (path.find(".html") != std::string::npos) {
        return Get::parseHtml(path);
    }

    // 图片
    auto it = std::find_if(IMGLIST.begin(), IMGLIST.end(), [&path](const std::string& ext) {
        return path.find(ext) != std::string::npos;
    });

    if (it != IMGLIST.end()) {
        return Get::parseImage(path);
    }

    // CSS
    if (path.find(".css") != std::string::npos) {
        return Get::parseCss(path);
    }

    // JavaScript
    if (path.find(".js") != std::string::npos) {
        return Get::parseJs(path);
    }

    // 默认响应
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain; charset=utf-8\r\n";
    response += "Content-Length: " + std::to_string(content.first) + "\r\n";
    response += "\r\n";
    response += content.second;

    return response;
}

std::string Get::parseHtml(std::string path) {
    std::pair<int, std::string> content = Get::getContent(path);
    // 构建响应
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html; charset=utf-8\r\n";
    response += "Content-Length: " + std::to_string(content.first) + "\r\n";
    response += "\r\n";
    response += content.second;

    return response;
}

std::string Get::parseImage(std::string path) {
    std::pair<int, std::string> content = Get::getContent(path);
    // 构建响应
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: image/" + path.substr(path.find_last_of(".") + 1) + "\r\n";
    response += "Content-Length: " + std::to_string(content.first) + "\r\n";
    response += "\r\n";
    response += content.second;

    return response;
}

std::string Get::parseCss(std::string path) {
    std::pair<int, std::string> content = Get::getContent(path);
    // 构建响应
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/css; charset=utf-8\r\n";
    response += "Content-Length: " + std::to_string(content.first) + "\r\n";
    response += "\r\n";
    response += content.second;

    return response;
}

std::string Get::parseJs(std::string path) {
    std::pair<int, std::string> content = Get::getContent(path);
    // 构建响应
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: application/javascript; charset=utf-8\r\n";
    response += "Content-Length: " + std::to_string(content.first) + "\r\n";
    response += "\r\n";
    response += content.second;
    return response;
}

