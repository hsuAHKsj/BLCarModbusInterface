
#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <client/TCPClient.h>
#include <memory>

typedef std::shared_ptr<TCPClient> TCPClientPtr;
using namespace std;

// 对平面管理器进行测试
class modbusControllerGtest : public testing::Test
{
protected:
    /// @brief 往平面里面插入一个平面
    void SetUp() override{
        
    };

    void TearDown() override
    {
        tcpClientPtr->disconnect();
    };

    std::string message;
    std::string response;
    TCPClientPtr tcpClientPtr;
};

TEST_F(modbusControllerGtest, modbusConnectionTest)
{
    tcpClientPtr = TCPClientPtr(new TCPClient("192.168.8.163", 8888));
    response = tcpClientPtr->sendAndReceive("CONNECT(192.168.1.120)");
    std::cout << "收到服务器的回复: " << response << std::endl;
    
    response = tcpClientPtr->sendAndReceive("GET_LEFT_MOTOR_STATE()");
    std::cout << "获取左轮状态: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("GET_RIGHT_MOTOR_STATE()");
    std::cout << "获取右轮状态: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
    std::cout << "获取升降机状态: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("GET_CAR_STATE()");
    std::cout << "获取车辆状态: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("GET_BACTTERTY_STATE()");
    std::cout << "获取电池状态: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("DISCONNECT()");
    std::cout << "断开链接: " << response << std::endl;

    // You can add your assertions here based on expected responses.
    // For example:
    // ASSERT_FLOAT_EQ(response, EXPECTED_FLOAT_VALUE);
    // ASSERT_EQ(response, EXPECTED_STRING_VALUE);
}


// TEST_F(modbusControllerGtest, motorControlTest)
// {
//     response = tcpClientPtr->sendAndReceive("CONNECT(192.168.1.120)");
//     std::cout << "收到服务器的回复: " << response << std::endl;

//     // Motor enable
//     response = tcpClientPtr->sendAndReceive("MOTOR_ENABLE()");
//     std::cout << "启动电机: " << response << std::endl;

//     // Set speed for left wheel motor
//     response = tcpClientPtr->sendAndReceive("SPEEDJ_LEFT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed
//     std::cout << "设置左轮电机速度: " << response << std::endl;

//     // Set speed for right wheel motor
//     response = tcpClientPtr->sendAndReceive("SPEEDJ_RIGHT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed
//     std::cout << "设置右轮电机速度: " << response << std::endl;

//     // Set speed for lifter motor
//     response = tcpClientPtr->sendAndReceive("SPEEDJ_LIFTER_MOTOR(1)"); // assuming speed value as 50, modify as needed
//     std::cout << "设置升降机电机速度: " << response << std::endl;

//     // Emergency stop
//     response = tcpClientPtr->sendAndReceive("EMERGENCY_STOP()");
//     std::cout << "紧急停车: " << response << std::endl;
// }


int main(int argc, char **argv)
{
  testing::GTEST_FLAG(catch_exceptions) = 1;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
