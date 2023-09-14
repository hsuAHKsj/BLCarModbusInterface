#include "modbus/modbus_wrapper.h"
#include "motorController/joint_driver.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;

int main(int argc, char **argv)
{
    // create a modbus object
    ModbusWrapper mbw("192.168.1.120", 502);
    const std::string csv_data = "../config/read_modbus_config.csv";
    mbw.parse_config(csv_data); 
    // connect with the server
    mbw.connect();

    // create a joint driver object
    JointDriver jd(&mbw);

    // jd.enable_joint("左驱动轮电机");
    // jd.enable_joint("右驱动轮电机");

    jd.enable_joint("左驱动轮电机");
    jd.enable_joint("右驱动轮电机");

    jd.updateData();
    int lift_joint = jd.get_joint_position("举升电机"); 
    int left_wheel = jd.get_joint_position("左驱动轮电机"); 
    int right_wheel = jd.get_joint_position("右驱动轮电机"); 


    cout <<"举升电机-pos = " << lift_joint << endl;
    cout <<"左驱动轮电机-pos = " << left_wheel << endl;
    cout <<"右驱动轮电机-pos = " << right_wheel << endl;
    // enable a joint

    double rad_per_second = -10; // 每秒钟转 0.01 个弧度, 
    jd.set_joint_speed("左驱动轮电机", rad_per_second);
    jd.set_joint_speed("右驱动轮电机", rad_per_second);

    int i = 0;

    // while(i < 50)
    // {
    //     jd.updateData();
    //     // double pos = jd.get_joint_position("左驱动轮电机"); 
    //     double l_spd = jd.read_joint_cur_speed("左驱动轮电机");
    //     double r_spd = jd.read_joint_cur_speed("右驱动轮电机");
    //     cout << "Speed: left = "  << l_spd << ", right = " << r_spd << endl;
    //     std::this_thread::sleep_for(milliseconds(60));
    //     i++;
    // }

    while(i < 1000)
    {
        jd.updateData();
        // double pos = jd.get_joint_position("左驱动轮电机"); 
        int lift_joint = jd.get_joint_position("举升电机"); 
        cout <<"举升电机-pos = " << lift_joint << endl;
        std::this_thread::sleep_for(milliseconds(60));
        i++;
    }

    jd.slow_down("左驱动轮电机");
    jd.slow_down("右驱动轮电机");
    
    // mbw.close();
    return 0;
}






