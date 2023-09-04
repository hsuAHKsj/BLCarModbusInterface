#include <client/TCPClient.h>

int main() {
    try {
        TCPClient client("192.168.1.62", 8888);

        while (true) {
            std::string message;
            std::cout << "请输入要发送的数据 (输入 'exit' 退出): ";
            std::getline(std::cin, message);

            if (message == "exit") {
                break;
            }

            std::string response = client.sendAndReceive(message);
            std::cout << "收到服务器的回复: " << response << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
