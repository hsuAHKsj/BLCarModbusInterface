#include <memory>
#include <regex>

using namespace std;

std::map<std::string, int> parseCommunicationProtocol(const std::string& jsonInput) {
    std::map<std::string, int> protocol;

    // 定义一个正则表达式模式来匹配键值对
    std::regex pattern("\"([^\"]+)\":(-?\\d+)");
    
    // 使用正则表达式迭代匹配的结果
    std::sregex_iterator iter(jsonInput.begin(), jsonInput.end(), pattern);
    std::sregex_iterator end;

    for (; iter != end; ++iter) {
        std::smatch match = *iter;
        std::string key = match[1];
        int value = std::stoi(match[2]);
        protocol[key] = value;
    }

    return protocol;
}

int32_t combine_high_low_word(uint16_t high_word, uint16_t low_word) {
    uint32_t result = static_cast<uint32_t>(high_word) << 16;
    result |= low_word;
    return static_cast<int32_t>(result);
}