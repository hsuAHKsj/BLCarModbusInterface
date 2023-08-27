#pragma once

#include "common.h"

class Helper {
public:
    Helper() {
        // 初始化 spdlog
    }

    void start() {
        // 模拟控制器开启成功
        spdlog::info("started successfully. Version: {}", getVersion());

        // 打印帮助信息
        printHelp();
    }

private:
    std::string getVersion() {
        return Version;
    }

    void printHelp() {
        spdlog::info("Available commands:");
        spdlog::info("  ");
        spdlog::info("CONNECT(ip)");
        spdlog::info("DISCONNECT()");
        spdlog::info("  ");
        spdlog::info("寄存器写入类参数接口");
        spdlog::info("MOTOR_ENABLE()");
        spdlog::info("SPEEDJ_LEFT_WHEEL_MOTOR(speed)");
        spdlog::info("SPEEDJ_RIGHT_WHEEL_MOTOR(speed)");
        spdlog::info("SPEEDJ_LIFTER_MOTOR(speed)");
        spdlog::info("EMERGENCY_STOP()");
        spdlog::info("  ");
        spdlog::info("获取状态类接口");
        spdlog::info("GET_LEFT_MOTOR_STATE()");
        spdlog::info("GET_RIGHT_MOTOR_STATE()");
        spdlog::info("GET_LIFTER_MOTOR_STATE()");
        spdlog::info("GET_CAR_STATE()");
        spdlog::info("GET_BACTTERTY_STATE()");

        
        // 添加其他支持的指令和描述
    }

private:
    
};