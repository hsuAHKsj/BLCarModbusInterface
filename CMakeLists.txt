cmake_minimum_required(VERSION 3.0)
project(server)

set(source ./src/server.cpp
            ./src/control.cpp
            ./src/modbus_wrapper.cpp
            ./src/control.cpp
)

# 添加可执行文件
add_executable(main ./src/main.cpp ${source})
# 链接sqdlog/C++库
target_link_libraries(main PRIVATE libspdlog.a -lpthread) 
target_include_directories(main PRIVATE /usr/local/include ./include)

