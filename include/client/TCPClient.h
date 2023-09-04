#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

class TCPClient {
private:
    int client_socket;
    sockaddr_in server_address;

public:
    TCPClient(const std::string& host, int port) {
        // Create socket
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
            throw std::runtime_error("Socket creation failed");
        }

        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        server_address.sin_addr.s_addr = inet_addr(host.c_str());

        // Connect to server
        if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "Failed to connect: " << strerror(errno) << std::endl;
            close(client_socket);
            throw std::runtime_error("Connection failed");
        }
    }

    ~TCPClient() {
        if (client_socket != -1) {
            close(client_socket);
        }
    }

    void disconnect() {
        if (client_socket != -1) {
            close(client_socket);
            client_socket = -1;
        }
    }

    std::string sendAndReceive(const std::string& message) {
        if (send(client_socket, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Failed to send data: " << strerror(errno) << std::endl;
            disconnect();
            throw std::runtime_error("Failed to send data");
        }

        char buffer[1024] = {0};
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            std::cerr << "Failed to receive data: " << strerror(errno) << std::endl;
            disconnect();
            throw std::runtime_error("Failed to receive data");
        }

        return std::string(buffer);
    }
};