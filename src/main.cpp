#include <iostream>
#include "common.h"
#include "help.h"
#include "server.h"
int main(){

    spdlog::set_level(spdlog::level::debug); // Set global log level to info

    spdlog::set_pattern("[%H:%M:%S %z] [%^%l%$] %v");      


    Helper help;
    help.start();
    SocketServer server(8888);
    server.start();

    return 0;
}