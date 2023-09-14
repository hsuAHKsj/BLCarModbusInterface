#include <memory>
#include <regex>

using namespace std;

// 使用正则表达式解析返回的数据，保存在哈希映射的数据结构中
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

// 合并高位和低位数据，得到关节位置
int32_t combine_high_low_word(uint16_t high_word, uint16_t low_word) {
    uint32_t result = static_cast<uint32_t>(high_word) << 16;
    result |= low_word;
    return static_cast<int32_t>(result);
}

//Todo:
//读取配置文件，构造静态函数，将RPM数据转化为国际单位数据，用于读取
// 将电机角速度（rad/s）转换为RPM
double convertToRPM(double rad_per_second, const int grating, const int reduction_ratio) {
    // 计算每秒旋转的圈数
    double circles_per_second = rad_per_second / (2 * M_PI);
    double rpm = circles_per_second * 60.0 * reduction_ratio;
    return rpm;
}

double convertToRadPerSecond(double rpm, const int grating, const int reduction_ratio) {
    // 将每分钟光栅编码器的增量转换为每秒光栅编码器的增量
    double encoder_increment_per_second = rpm /reduction_ratio / 60.0;

    // 转换为物理速度（弧度/秒）
    double rad_per_second = encoder_increment_per_second * (2 * M_PI);

    return rad_per_second;
}
//读取配置文件，将国际单位数据重新转化回RPM，用于写入
