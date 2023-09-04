// joint_driver.h
#ifndef JOINT_DRIVER_H
#define JOINT_DRIVER_H

#include "modbus/modbus_wrapper.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <cmath>

// #define LIFT_GRATING 65535
// #define WHEEL_GRATING 10000
#define buffer_size 30

using namespace std;

class JointDriver {
public:
    JointDriver(ModbusWrapper *modbus_wrapper);
    // ~JointDriver()
    // {
    //     modbus=nullptr;
    // }

    // 使能相关指令
    void enable_joint(const std::string &description);
    void disable_joint(const std::string &description);

    // 写关节运动指令，单位为 脉冲/分钟 rpm
    void set_joint_rpm(const std::string &description, int speed);
    // 写关节速度，单位为 rad/s
    void set_joint_speed(const std::string &description, const double speed);
    void slow_down(const std::string &description);
    // 设置机器人运动到指定位置
    bool move_to(const std::string &description, int jposition);

    // 读关节运动指令，单位为 脉冲/分钟 rpm
    int read_joint_rpm(const std::string &description);
    // 读电机当前速度，单位为 rad/s
    double read_joint_cur_speed(const std::string &description);

    // 读取电机当前位置
    int_fast32_t get_joint_position(const std::string &description);
    void updateData();

private:
    ModbusWrapper *modbus;
    uint16_t read_holding_regs[buffer_size];
    int32_t combine_high_low_word(uint16_t high_word, uint16_t low_word);
    double convertToRPM(double rad_per_second, const int grating, const int reduction_ratio);
    double convertToRadPerSecond(double rpm, const int grating, const int reduction_ratio); 
};

#endif // JO