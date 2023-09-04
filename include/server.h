#pragma once


#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <regex>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "control.h"
#include "common.h"
// // 简单线程池类
// class ThreadPool {
// public:
//     ThreadPool(size_t numThreads) : stop(false) {
//         for (size_t i = 0; i < numThreads; ++i) {
//             threads.emplace_back([this] {
//                 while (true) {
//                     std::function<void()> task;

//                     {
//                         std::unique_lock<std::mutex> lock(this->queueMutex);
//                         this->condition.wait(lock, [this] {
//                             return this->stop || !this->tasks.empty();
//                         });

//                         if (this->stop && this->tasks.empty()) {
//                             return;
//                         }

//                         task = std::move(this->tasks.front());
//                         this->tasks.pop();
//                     }

//                     task();
//                 }
//             });
//         }
//     }

//     ~ThreadPool() {
//         {
//             std::unique_lock<std::mutex> lock(queueMutex);
//             stop = true;
//         }
//         condition.notify_all();
//         for (std::thread &thread : threads) {
//             thread.join();
//         }
//     }

//     template <class F>
//     void enqueue(F &&f) {
//         {
//             std::unique_lock<std::mutex> lock(queueMutex);
//             if (stop) {
//                 throw std::runtime_error("enqueue on stopped ThreadPool");
//             }
//             tasks.emplace(std::forward<F>(f));
//         }
//         condition.notify_one();
//     }

// private:
//     std::vector<std::thread> threads;
//     std::queue<std::function<void()>> tasks;
//     std::mutex queueMutex;
//     std::condition_variable condition;
//     bool stop;
// };

// Socket服务端
class SocketServer {
public:
    SocketServer(int port) : serverPort(port) {}

    void start();

    void stop() {
        close(serverSocket);
    }

private:
    void handleClient(int clientSocket) ;

    int serverSocket;
    int serverPort;

    std::mutex queueMutex;
    std::condition_variable condition;
};

