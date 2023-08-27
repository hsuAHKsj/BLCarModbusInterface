#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "control.h"

// class CommunicationThread {
// public:
//     CommunicationThread(Controller &controller)
//         : controller(controller), stopFlag(false) {}

//     void start() {
//         thread = std::thread(&CommunicationThread::run, this);
//     }

//     void stop() {
//         {
//             std::lock_guard<std::mutex> lock(mutex);
//             stopFlag = true;
//         }
//         condition.notify_one();
//         thread.join();
//     }

// private:
//     void run() {
//         while (true) {
//             {
//                 std::unique_lock<std::mutex> lock(mutex);
//                 if (stopFlag) {
//                     break;
//                 }

//                 // // 读取寄存器状态并进行存储
//                 // int registerValue = controller.readRegister();
//                 // // TODO: 存储寄存器状态的操作

//                 // // 设置三个电机的速度
//                 // motorController.setSpeed(1, registerValue);
//                 // motorController.setSpeed(2, registerValue * 2);
//                 // motorController.setSpeed(3, registerValue * 3);
//             }
//             condition.wait_for(lock, std::chrono::seconds(1)); // 每秒执行一次
//         }
//     }

//     Controller &controller;
//     std::thread thread;
//     bool stopFlag;
//     std::mutex mutex;
//     std::condition_variable condition;
// };

// int main() {
//     Controller controller;
//     MotorController motorController;
//     CommunicationThread communicationThread(controller, motorController);
//     communicationThread.start();

//     // 让线程运行一段时间
//     std::this_thread::sleep_for(std::chrono::seconds(10));

//     communicationThread.stop();

//     return 0;
// }
