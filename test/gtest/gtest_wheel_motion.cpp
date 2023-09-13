
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
    std::string response_l;
    std::string response_r;
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

    response_l = tcpClientPtr->sendAndReceive("GET_LEFT_MOTOR_STATE()");
    response_r = tcpClientPtr->sendAndReceive("GET_RIGHT_MOTOR_STATE()");

    std::map<std::string, int> mapVector_l = parseCommunicationProtocol(response_l);
    int32_t PositionPre_l = combine_high_low_word(mapVector_l["PositionH1"], mapVector_l["PositionL1"]);

    std::map<std::string, int> mapVector_r = parseCommunicationProtocol(response_r);
    int32_t PositionPre_r = combine_high_low_word(mapVector_r["PositionH2"], mapVector_r["PositionL2"]);

    std::cout << "获取两个轮子初始状态: left = " << PositionPre_l << ", right = "<< PositionPre_r << std::endl;

    ASSERT_NE(PositionPre_l, 0);
    ASSERT_NE(PositionPre_r, 0);


    double timeInterval = 1;
    int time = 0;

    response_l = tcpClientPtr->sendAndReceive("SPEEDJ_LEFT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed
    response_r = tcpClientPtr->sendAndReceive("SPEEDJ_RIGHT_WHEEL_MOTOR(1)"); // assuming speed value as 50, modify as needed

    while(time++ < 10)
    {
        sleep(timeInterval);
        response_l = tcpClientPtr->sendAndReceive("GET_LEFT_MOTOR_STATE()");
        response_r = tcpClientPtr->sendAndReceive("GET_RIGHT_MOTOR_STATE()");

        std::map<std::string, int> mapVector_l = parseCommunicationProtocol(response_l);
        int32_t Position_l = combine_high_low_word(mapVector_l["PositionH1"], mapVector_l["PositionL1"]);

        std::map<std::string, int> mapVector_r = parseCommunicationProtocol(response_r);
        int32_t Position_r = combine_high_low_word(mapVector_r["PositionH2"], mapVector_r["PositionL2"]);
        
        std::cout << "获取左轮状态: " << response_l << std::endl;
        std::cout << "获取右轮状态: " << response_r << std::endl;

        std::cout << "获取两个轮子初始状态: left = " << Position_l << ", right = "<< Position_r << std::endl;
        
        ASSERT_TRUE(Position_l > PositionPre_l);
        ASSERT_TRUE(Position_r > PositionPre_r);

        PositionPre_l = Position_l;
        PositionPre_r = Position_r;
    }

    response_l = tcpClientPtr->sendAndReceive("SPEEDJ_LEFT_WHEEL_MOTOR(0)"); // assuming speed value as 50, modify as needed
    response_r = tcpClientPtr->sendAndReceive("SPEEDJ_RIGHT_WHEEL_MOTOR(0)"); 
    sleep(timeInterval);

    response_l = tcpClientPtr->sendAndReceive("GET_LEFT_MOTOR_STATE()");
    mapVector_l = parseCommunicationProtocol(response_l);
    response_r = tcpClientPtr->sendAndReceive("GET_RIGHT_MOTOR_STATE()");
    mapVector_r = parseCommunicationProtocol(response_r);
    
    ASSERT_EQ(mapVector_l["Speed1"], 0) ;
    ASSERT_EQ(mapVector_r["Speed2"], 0) ;

    response = tcpClientPtr->sendAndReceive("DISCONNECT()");
    std::cout << "断开链接: " << response << std::endl;
}

int main(int argc, char **argv)
{
  testing::GTEST_FLAG(catch_exceptions) = 1;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
