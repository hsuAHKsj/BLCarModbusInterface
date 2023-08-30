import socket
<<<<<<< Updated upstream

# 客户端配置
host = '192.168.1.62'  # 服务器的IP地址
=======
host = '192.168.8.163'  # 服务器的IP地址
>>>>>>> Stashed changes
port = 8888        # 服务器的端口号

# 创建Socket对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接到服务器
client_socket.connect((host, port))

while True:
    # 从终端输入要发送的数据
    message = input("请输入要发送的数据 (输入 'exit' 退出): ")

    # 发送数据到服务器
    client_socket.sendall(message.encode())

    if message == 'exit':
        break

    # 接收服务器发送的数据
    data = client_socket.recv(1024)

    # 打印收到的数据
    print("收到服务器的回复:", data.decode())

# 关闭Socket连接
client_socket.close()