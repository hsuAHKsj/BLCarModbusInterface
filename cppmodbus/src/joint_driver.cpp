
#include <motorController/joint_driver.h>
#include "motorController/motor.h"

JointDriver::JointDriver(ModbusWrapper *modbus_wrapper) : modbus(modbus_wrapper) {
}

void JointDriver::enable_joint(const std::string &description) {
std::string control_word_desc = description + "使能-控制字";
modbus->write_register(control_word_desc, 15);
}

void JointDriver::disable_joint(const std::string &description) {
std::string control_word_desc = description + "使能-控制字";
modbus->write_register(control_word_desc, 0);
}

// 写机器人运动关节
void JointDriver::set_joint_speed(const std::string &description, const double speed) {
    
    MotorHelper motorHelper;
    MotorParameters motorMeterParam = motorHelper.getMotorParameters(description);
    double rpm = convertToRPM(speed, motorMeterParam.grating, motorMeterParam.reduction_ratio);
    
    // cout << "motorMeterParam.grating" << motorMeterParam.grating << endl;
    // cout << "motorMeterParam.reduction_ratio" << motorMeterParam.reduction_ratio << endl;
    set_joint_rpm(description, rpm);
}

void JointDriver::slow_down(const std::string &description)
{
    set_joint_rpm(description, 0);
};

void JointDriver::set_joint_rpm(const std::string &description, int speed) {

    MotorHelper motorHelper;
    MotorParameters motorMeterParam = motorHelper.getMotorParameters(description);
    if(abs(speed)> motorMeterParam.max_rpm)
    {
        double sign = (speed > 0) - (speed < 0);
        speed = int(sign*motorMeterParam.max_rpm);
    }
    cout << "rpm speed = " << speed << endl;
    std::string speed_desc = description + "-目标速度RPM";
    modbus->write_register(speed_desc, speed);
}


int JointDriver::read_joint_rpm(const std::string &description)
{
    int value = 0;
    if(description == "左驱动轮电机") value = read_holding_regs[6];
    else if (description == "右驱动轮电机") value = read_holding_regs[16];
    else if (description == "举升电机") value = read_holding_regs[26];
    return static_cast<short>(value);
};

// 读关节运动状态
int_fast32_t JointDriver::get_joint_position(const std::string &description) {
    uint16_t high;
    uint16_t low;
    if(description == "左驱动轮电机")
    {
        high = read_holding_regs[7];
        low = read_holding_regs[8];
    } 
    else if (description == "右驱动轮电机") 
    {
        high = read_holding_regs[17];
        low = read_holding_regs[18];
    } 
    else if (description == "举升电机")
    {
        
        high = read_holding_regs[27];
        low = read_holding_regs[28];
    }
    int32_t ret = combine_high_low_word(high, low);
    // cout << "high =" << high << "," << "low = " << low << endl;
    return ret;
}

// 读电机当前速度，单位为 rad/s
double JointDriver::read_joint_cur_speed(const std::string &description)
{
    int rpm = read_joint_rpm(description);
    cout << "Readed rpm speed = " << rpm << endl;
    MotorHelper motorHelper;
    MotorParameters motorMeterParam = motorHelper.getMotorParameters(description);
    double rps = convertToRadPerSecond(rpm, motorMeterParam.grating, motorMeterParam.reduction_ratio);
    return rps; 
};

void JointDriver::updateData()
{
    modbus->mb_ptr->modbus_read_holding_registers(810, 20, read_holding_regs);
}

int32_t JointDriver::combine_high_low_word(uint16_t high_word, uint16_t low_word) {
    uint32_t result = static_cast<uint32_t>(high_word) << 16;
    result |= low_word;
    return static_cast<int32_t>(result);
}

// 将电机角速度（rad/s）转换为RPM
double JointDriver::convertToRPM(double rad_per_second, const int grating, const int reduction_ratio) {
    // 计算每秒旋转的圈数
    double circles_per_second = rad_per_second / (2 * M_PI);
    double rpm = circles_per_second * 60.0 * reduction_ratio;
    return rpm;
}

double JointDriver::convertToRadPerSecond(double rpm, const int grating, const int reduction_ratio) {
    // 将每分钟光栅编码器的增量转换为每秒光栅编码器的增量
    double encoder_increment_per_second = rpm /reduction_ratio / 60.0;

    // 转换为物理速度（弧度/秒）
    double rad_per_second = encoder_increment_per_second * (2 * M_PI);

    return rad_per_second;
}