#include "utils.hpp"
#include <algorithm>

bool StringToBool(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s == "true" || s == "1" || s == "yes" || s == "on"){
        return true;
    }
    return false;
}
std::string VectorStringToString(const std::vector<std::string> &vec){
    if (vec.empty()) return "";
    std::string result = vec[0];
    for (size_t i = 1; i < vec.size(); ++i){
        result += " " + vec[i];
    }
    return result;
}
