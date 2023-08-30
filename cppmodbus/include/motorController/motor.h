#pragma once
#include <string>

// 电机参数结构体
struct MotorParameters {
    double grating;
    double reduction_ratio;
    double zero_inc;
    double max_inc;
    double min_inc;
    double max_rpm;
};

class MotorHelper {
public:
    // 定义电机类型常量
    static const std::string LIFT_MOTOR;
    static const std::string LEFT_WHEEL_MOTOR;
    static const std::string RUGHT_WHEEL_MOTOR;

    // 定义光栅值和减速比常量
    static const double LIFT_GRATING;
    static const double WHEEL_GRATING;
    static const double LIFT_REDUCTION_RATIO;
    static const double WHEEL_REDUCTION_RATIO;

    static const double LIFT_ZERO; 
    static const double LIFT_MAX; 
    static const double LIFT_MIN; 
    static const double WHEEL_MAX_RPM; 

    // 根据电机类型获取光栅值和减速比
    MotorParameters getMotorParameters(const std::string& motor_type) {
        MotorParameters params;

        if (motor_type == LIFT_MOTOR) {
            params.grating = LIFT_GRATING;
            params.reduction_ratio = LIFT_REDUCTION_RATIO;
            params.zero_inc = LIFT_ZERO;
            params.max_inc = LIFT_MAX;
            params.min_inc = LIFT_MIN;
        } else if (motor_type == LEFT_WHEEL_MOTOR || motor_type == RUGHT_WHEEL_MOTOR) {
            params.grating = WHEEL_GRATING;
            params.reduction_ratio = WHEEL_REDUCTION_RATIO;
            params.max_rpm = WHEEL_MAX_RPM;
        }

        return params;
    }
};

// 初始化静态成员变量
const std::string MotorHelper::LIFT_MOTOR = "举升电机";
const std::string MotorHelper::LEFT_WHEEL_MOTOR = "左驱动轮电机";
const std::string MotorHelper::RUGHT_WHEEL_MOTOR = "右驱动轮电机";
const double MotorHelper::LIFT_GRATING = 65535.0;
const double MotorHelper::WHEEL_GRATING = 10000.0;
const double MotorHelper::LIFT_REDUCTION_RATIO = 19.0;
const double MotorHelper::WHEEL_REDUCTION_RATIO = 19.0;
const double MotorHelper::WHEEL_MAX_RPM = 100;
const double MotorHelper::LIFT_ZERO = 0;
const double MotorHelper::LIFT_MAX = 0;
const double MotorHelper::LIFT_MIN = 0;
