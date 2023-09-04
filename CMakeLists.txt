cmake_minimum_required(VERSION 3.0)
project(server)

set(source ./src/server.cpp
            ./src/control.cpp
            ./src/modbus_wrapper.cpp
            ./src/control.cpp
)

include_directories(./include)
link_directories(./lib)

include_directories(./lib/spdlog-1.12.0/include)
include_directories(./lib/json-develop/include)

# 添加可执行文件
add_executable(main ./src/main.cpp ${source})
# 链接sqdlog/C++库
target_link_libraries(main PRIVATE libspdlog.a -lpthread) 

# 添加可执行文件
add_executable(testTCPClient test/cpp/TCPClient.cpp)
target_link_libraries(testTCPClient libspdlog.a) 
