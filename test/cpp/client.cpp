#include <iostream>
#include <string>
#include <cstring>      // For `memset` and `strerror`
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>     // For `close`

int main() {
    const char *host = "192.168.1.62";
    int port = 8888;

    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return -1;
    }

    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(host);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Failed to connect: " << strerror(errno) << std::endl;
        close(client_socket);
        return -1;
    }

    while (true) {
        std::string message;
        std::cout << "请输入要发送的数据 (输入 'exit' 退出): ";
        std::getline(std::cin, message);

        // Send data to server
        if (send(client_socket, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Failed to send data: " << strerror(errno) << std::endl;
            break;
        }

        if (message == "exit") {
            break;
        }

        char buffer[1024] = {0};
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            std::cerr << "Failed to receive data: " << strerror(errno) << std::endl;
            break;
        }

        std::cout << "收到服务器的回复: " << buffer << std::endl;
    }

    close(client_socket);
    return 0;
}
