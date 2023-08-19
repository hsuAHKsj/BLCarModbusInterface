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
 
        spdlog::info("CONNECT(ip)");
        spdlog::info("DISCONNECT()");
        spdlog::info("寄存器写入类参数接口");
        spdlog::info("MOTOR _ENABLE()");
        spdlog::info("SPEEDJ. _LEFT. _WHEEL MOTOR(speed)");
        spdlog::info("SPEEDJ_ RIGHT _WHEEL MOTOR(speed)");
        spdlog::info("SPEEDJ_ LIFTER MOTOR(speed)");
        spdlog::info("EMERGENCY. STOP()");
        
        spdlog::info("获取状态类接口");
        spdlog::info("GET_ LEFT _MOTOR_ STATE()");
        spdlog::info("GET_ RIGHT MOTOR_ STATE()");
        spdlog::info("GET_ LIFTER MOTOR STATE()");
        spdlog::info("GET CAR. STATE()");
        spdlog::info("GET_ BACTTERTY STATE()");

        
        // 添加其他支持的指令和描述
    }

private:
    
};