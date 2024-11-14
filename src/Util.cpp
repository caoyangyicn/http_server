#include "Util.h"

vector<string> Util::StringToVecByEnter(string request){
    vector<string> result;
    stringstream ss(request);
    string line;
    while (getline(ss, line)) {
        result.push_back(line);
    }
    return result;
}

vector<string> Util::StringToVecBySpace(string request) {
    vector<string> result;
    istringstream ss(request);
    string word;
    while (ss >> word) {
        result.push_back(word);
    }
    return result;
}