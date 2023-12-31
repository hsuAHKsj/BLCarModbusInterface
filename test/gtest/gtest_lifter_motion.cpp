
#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <client/TCPClient.h>
#include <utility/utility.h> 
#include <memory>
#include <regex>

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

TEST_F(modbusControllerGtest, testConnection)
{
    tcpClientPtr = TCPClientPtr(new TCPClient("192.168.1.62", 8888));
    response = tcpClientPtr->sendAndReceive("CONNECT(192.168.1.120)");
    ASSERT_EQ(response, "{connect success}");
}

TEST_F(modbusControllerGtest, modbusConnectionTest)
{
    tcpClientPtr = TCPClientPtr(new TCPClient("192.168.1.62", 8888));
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

    response = tcpClientPtr->sendAndReceive("GET_LIFTER_POSITION_IO()");
    std::cout << "获取货叉升降限位: " << response << std::endl;

    // response = tcpClientPtr->sendAndReceive("GET_LIFTER_PEAK_IO()");
    // std::cout << "获取货叉尖限位: " << response << std::endl;

    // response = tcpClientPtr->sendAndReceive("GET_COLLISION_ARARM_IO()");
    // std::cout << "获取触碰报警限位: " << response << std::endl;

    // response = tcpClientPtr->sendAndReceive("DISCONNECT()");
    // std::cout << "断开链接: " << response << std::endl;
    // You can add your assertions here based on expected responses.
    // For example:
    // ASSERT_FLOAT_EQ(response, EXPECTED_FLOAT_VALUE);
    // ASSERT_EQ(response, EXPECTED_STRING_VALUE);
}

// 将举升的叉子运动到上限位，并获取限位开关的状态
TEST_F(modbusControllerGtest, moveLifter2UpperLimiation)
{
    tcpClientPtr = TCPClientPtr(new TCPClient("192.168.1.62", 8888));
    response = tcpClientPtr->sendAndReceive("CONNECT(192.168.1.120)");
    std::cout << "收到服务器的回复: " << response << std::endl;

    // Motor enable
    response = tcpClientPtr->sendAndReceive("MOTOR_ENABLE()");
    std::cout << "启动电机: " << response << std::endl;

    response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
    std::cout << "获取升降机初始状态: " << response << std::endl;
    std::map<std::string, int> mapVector = parseCommunicationProtocol(response);
    int32_t LifterPositionPre = combine_high_low_word(mapVector["PositionH3"], mapVector["PositionL3"]);
    ASSERT_NE(LifterPositionPre, 0);

    double timeInterval = 1;
    int time = 0;

    response = tcpClientPtr->sendAndReceive("SPEEDJ_LIFTER_MOTOR(300)"); // assuming speed value as 50, modify as needed
    std::cout << "设置升降机电机速度: " << response << std::endl;

    while(time++ < 10)
    {
        sleep(timeInterval);
        response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
        std::cout << "获取升降机状态: " << response << std::endl;
        std::map<std::string, int> mapVector = parseCommunicationProtocol(response);
        int32_t LifterPosition = combine_high_low_word(mapVector["PositionH3"], mapVector["PositionL3"]);
        cout << "Lifter Position = " << LifterPosition << endl;
        ASSERT_TRUE(LifterPosition > LifterPositionPre);
        LifterPositionPre = LifterPosition;
    }

    response = tcpClientPtr->sendAndReceive("SPEEDJ_LIFTER_MOTOR(-300)"); 
    while(time++ < 10)
    {
        sleep(timeInterval);
        response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
        std::cout << "获取升降机状态: " << response << std::endl;
        std::map<std::string, int> mapVector = parseCommunicationProtocol(response);
        int32_t LifterPosition = combine_high_low_word(mapVector["PositionH3"], mapVector["PositionL3"]);
        cout << "Lifter Position = " << LifterPosition << endl;
        ASSERT_TRUE(LifterPosition < LifterPositionPre) ;
        LifterPositionPre = LifterPosition;
    }

    response = tcpClientPtr->sendAndReceive("SPEEDJ_LIFTER_MOTOR(0)"); 
    sleep(timeInterval);
    std::cout << "设置升降机电机速度: " << response << std::endl;
    response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
    mapVector = parseCommunicationProtocol(response);
    
    ASSERT_EQ(mapVector["Speed3"], 0) ;
    response = tcpClientPtr->sendAndReceive("DISCONNECT()");
    std::cout << "断开链接: " << response << std::endl;
}



// TEST_F(modbusControllerGtest, motorControlTest)
// {
//     tcpClientPtr = TCPClientPtr(new TCPClient("192.168.1.62", 8888));
//     response = tcpClientPtr->sendAndReceive("CONNECT(192.168.1.120)");
//     std::cout << "收到服务器的回复: " << response << std::endl;

//     // Motor enable
//     response = tcpClientPtr->sendAndReceive("MOTOR_ENABLE()");
//     std::cout << "启动电机: " << response << std::endl;

//     // // Set speed for left wheel motor
//     // response = tcpClientPtr->sendAndReceive("SPEEDJ_LEFT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed
//     // std::cout << "设置左轮电机速度: " << response << std::endl;

//     // // Set speed for right wheel motor
//     // response = tcpClientPtr->sendAndReceive("SPEEDJ_RIGHT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed
//     // std::cout << "设置右轮电机速度: " << response << std::endl;

//     // Set speed for lifter motor
//     response = tcpClientPtr->sendAndReceive("SPEEDJ_LIFTER_MOTOR(3)"); // assuming speed value as 50, modify as needed
//     std::cout << "设置升降机电机速度: " << response << std::endl;

//     for(int i = 0; i < 10; i ++)
//     {
//         response = tcpClientPtr->sendAndReceive("GET_LIFTER_MOTOR_STATE()");
//         std::cout << "获取升降机状态: " << response << std::endl;
//         sleep(1.0);
//     }

//     // Emergency stop
//     response = tcpClientPtr->sendAndReceive("EMERGENCY_STOP()");
//     std::cout << "紧急停车: " << response << std::endl;
    
//     response = tcpClientPtr->sendAndReceive("DISCONNECT()");
//     std::cout << "断开链接: " << response << std::endl;
// }


int main(int argc, char **argv)
{
  testing::GTEST_FLAG(catch_exceptions) = 1;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
