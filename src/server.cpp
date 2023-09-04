#include "server.h"

void SocketServer::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);

    if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1) {
        perror("Failed to bind socket");
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Failed to listen on socket");
        close(serverSocket);
        return;
    }

    // ThreadPool threadPool(5);
    spdlog::info("server start... port:{}\r\n", serverPort);
    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrLen);
        if (clientSocket == -1) {
            spdlog::warn("connect client failed clientSocket == -1\r\n");
            continue;
        }


        std::thread(std::bind(&SocketServer::handleClient, this, clientSocket)).detach();
        // threadPool.enqueue([this, clientSocket] {
        //     handleClient(clientSocket);
        // });
    }
}



 // 正则表达式解析
static std::regex mconnect("CONNECT\\((\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})\\)");
static std::regex disconnect("DISCONNECT\\(\\)");


static std::regex emergency_stop("EMERGENCY_STOP\\(\\)");
static std::regex motor_enable("MOTOR_ENABLE\\(\\)");

static std::regex speedj_left_wheel_motor(R"(SPEEDJ_LEFT_WHEEL_MOTOR\((-?\d+)\))");
static std::regex speedj_right_wheel_motor(R"(SPEEDJ_RIGHT_WHEEL_MOTOR\((-?\d+)\))");
static std::regex speedj_lifter_motor(R"(SPEEDJ_LIFTER_MOTOR\((-?\d+)\))");


static std::regex get_left_motor_state("GET_LEFT_MOTOR_STATE\\(\\)");
static int left_motor_state;

static std::regex get_right_motor_state("GET_RIGHT_MOTOR_STATE\\(\\)");
static int right_motor_state;

static std::regex get_lifter_motor_state("GET_LIFTER_MOTOR_STATE\\(\\)");
static int lifter_motor_state;

static std::regex get_car_state("GET_CAR_STATE\\(\\)");
static int car_state;

static std::regex get_bactterty_state("GET_BACTTERTY_STATE\\(\\)");
static int battery_state;


void SocketServer::handleClient(int clientSocket) {

    char buffer[1024];
    std::shared_ptr<Controller> mcontroller = std::make_shared<Controller>();
    bool connect_status = false;
    while(1){
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            close(clientSocket);
            spdlog::info("clientSocket close");
            return;
        }

        buffer[bytesRead] = '\0';
        std::string request(buffer);
        spdlog::info("request: {}", request);
        std::smatch match;
        int ret = 0;

        std::string fail1 = "{failed:-1}";//connect failed
        std::string fail2 = "{failed:-2}";//emergency stop

        if (std::regex_search(request, match, mconnect)) {
            std::string ip = std::string(match[1]);
            ret = mcontroller->CONNECT(ip);
            if(ret != 0) {
                spdlog::info(" {} connect failed\r\n", ip);
                send(clientSocket, fail1.c_str(), fail1.size(), 0);
                continue;
            }
            connect_status = true;
            spdlog::info(" {} connect \r\n", ip);
            std::string success = "{connect success}";
            send(clientSocket, success.c_str(), success.size(), 0);
            continue;
        } 
        
        if(!connect_status) {
            spdlog::info("connect failed\r\n");
            send(clientSocket, fail1.c_str(), fail1.size(), 0);
            continue;
        }
        
        if(std::regex_search(request, match, disconnect)) {
            ret = mcontroller->DISCONNECT();
            mcontroller->run();
            spdlog::info("disconnect \r\n");
            break;
        }else if(std::regex_search(request, match, emergency_stop)){
            ret = mcontroller->EMERGENCY_STOP();
            spdlog::info("emergency_stop \r\n");

        }else if(std::regex_search(request, match, motor_enable)){
            ret = mcontroller->MOTOR_ENABLE();
            spdlog::info("motor_enable \r\n");

        }else if(std::regex_search(request, match, speedj_left_wheel_motor)){
            std::string sspeed = std::string(match[1]);
            int speed = std::stoi(sspeed);
            ret = mcontroller->SPEEDJ_LEFT_WHEEL_MOTOR(static_cast<int16_t>(speed));
            if(ret ==  EMERGENCY_STOP_FLAG ) {
                send(clientSocket, fail2.c_str(), fail2.size(), 0);
                continue;
            }
            spdlog::info(" {} speedj_left_wheel_motor {}\r\n", mcontroller->get_ip(), speed);

        }else if(std::regex_search(request, match, speedj_right_wheel_motor)){
            std::string sspeed = std::string(match[1]);
            int speed = std::stoi(sspeed);
            ret = mcontroller->SPEEDJ_RIGHT_WHEEL_MOTOR(static_cast<int16_t>(speed));
            if(ret ==  EMERGENCY_STOP_FLAG ) {
                send(clientSocket, fail2.c_str(), fail2.size(), 0);
                continue;
            }
            spdlog::info(" {} speedj_right_wheel_motor {} \r\n", mcontroller->get_ip(), speed);

        }else if(std::regex_search(request, match, speedj_lifter_motor)){
            std::string sspeed = std::string(match[1]);
            int speed = std::stoi(sspeed);
            ret = mcontroller->SPEEDJ_LIFTER_MOTOR(static_cast<int16_t>(speed));
            if(ret ==  EMERGENCY_STOP_FLAG ) {
                send(clientSocket, fail2.c_str(), fail2.size(), 0);
                continue;
            }
            spdlog::info(" {} speedj_lifter_motor {} \r\n", mcontroller->get_ip(), speed);

        }else if(std::regex_search(request, match, get_left_motor_state)){
            std::string response = mcontroller->GET_LEFT_MOTOR_STATE();
            spdlog::info(" {} get_left_motor_state {}\r\n", mcontroller->get_ip(),response);
            
            send(clientSocket, response.c_str(), response.size(), 0);
            continue;

        }else if(std::regex_search(request, match, get_right_motor_state)){
            std::string response  = mcontroller->GET_RIGHT_MOTOR_STATE();
            spdlog::info(" {} get_right_motor_state {}\r\n", mcontroller->get_ip(), response);
            send(clientSocket, response.c_str(), response.size(), 0);
            continue;

        }else if(std::regex_search(request, match, get_lifter_motor_state)){
            std::string response  = mcontroller->GET_LIFTER_MOTOR_STATE();
            spdlog::info(" {} get_lifter_motor_state \r\n", mcontroller->get_ip(), response);

            send(clientSocket, response.c_str(), response.size(), 0);
            continue;

        }else if(std::regex_search(request, match, get_car_state)){
            std::string response  = mcontroller->GET_CAR_STATE();
            spdlog::info(" {} get_car_state {}\r\n", mcontroller->get_ip(), response);

            send(clientSocket, response.c_str(), response.size(), 0);
            continue;

        }else if(std::regex_search(request, match, get_bactterty_state)){
            std::string response  = mcontroller->GET_BACTTERTY_STATE();
            spdlog::info(" {} get_bactterty_state {} \r\n", mcontroller->get_ip(), response);

            send(clientSocket, response.c_str(), response.size(), 0);
            continue;

        }else {
            spdlog::info(" instruction error \r\n");
            std::string response = "instruction error";
            send(clientSocket, response.c_str(), response.size(), 0);
            continue;
        }


        std::string success = "{success}";
        send(clientSocket, success.c_str(), success.size(), 0);

    }
    close(clientSocket);
}





// int main() {
//     SocketServer server(8080);
//     server.start();
//     return 0;
// }
