#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

class Get {
public:
    static std::string getResponse(std::string request);
    static std::pair<int, std::string> getContent(std::string path);
    static std::string parseHtml(std::string path);
    static std::string parseImage(std::string path);
    static std::string parseCss(std::string path);
    static std::string parseJs(std::string path);
};