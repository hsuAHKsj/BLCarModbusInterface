#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <thread>
#include "modbus_wrapper.h"
#include "motorcontrollersql.h"
#include "common.h"

enum MotorDescription{
     controlWord1,
     statusWord1,
     currentSpeed1,
     currentPositionL1,
     currentPositionH1,

     controlWord2,
     statusWord2,
     currentSpeed2,
     currentPositionL2,
     currentPositionH2,

     controlWord3,
     statusWord3,
     currentSpeed3,
     currentPositionL3,
     currentPositionH3,
};

const std::string control_Word1="左驱动轮电机使能-控制字";
const std::string status_Word1="左驱动轮电机-状态字";
const std::string current_Speed1="左驱动轮电机-当前速度RPM";
const std::string current_PositionL1="左驱动轮电机-当前位置L";
const std::string current_PositionH1="左驱动轮电机-当前位置H";

const std::string control_Word2="右驱动轮电机使能-控制字";
const std::string status_Word2="右驱动轮电机-状态字";
const std::string current_Speed2="右驱动轮电机-当前速度RPM";
const std::string current_PositionL2="右驱动轮电机-当前位置L";
const std::string current_PositionH2="右驱动轮电机-当前位置H";

const std::string control_Word3="举升电机使能-控制字";
const std::string status_Word3="举升电机-状态字";
const std::string current_Speed3="举升电机-当前速度RPM";
const std::string current_PositionL3="举升电机-当前位置L";
const std::string current_PositionH3="举升电机-当前位置H";

class Motorcontrol{
    public:
    Motorcontrol(ModbusWrapper *modubs=nullptr):modbusmotor(std::shared_ptr<ModbusWrapper>(modubs)),
        motorController(server, user, password, database)
    {
            

    }
    ~Motorcontrol(){

    }

    void read_holding_register(const MotorDescription &description);

    void start() {
        
        motor_thread = std::move(std::thread([this](){
            while(exit_flag) {
                read_holding_register(controlWord1);
                read_holding_register(statusWord1);
                read_holding_register(currentSpeed1);
                read_holding_register(currentPositionL1);
                read_holding_register(currentPositionH1);

                read_holding_register(controlWord2);
                read_holding_register(statusWord2);
                read_holding_register(currentSpeed2);
                read_holding_register(currentPositionL2);
                read_holding_register(currentPositionH2);

                read_holding_register(controlWord3);
                read_holding_register(statusWord3);
                read_holding_register(currentSpeed3);
                read_holding_register(currentPositionL3);
                read_holding_register(currentPositionH3);


                if(    control1 != controlold1
                    || status1 != statusold1
                    ||  Speed1 != Speedold1
                    || PositionL1 != PositionLold1
                    || PositionH1 != PositionHold1
                    || control2 != controlold2
                    || status2 != statusold2
                    ||  Speed2 != Speedold2
                    || PositionL2 != PositionLold2
                    || PositionH2 != PositionHold2
                    || control3 != controlold3
                    || status3 != statusold3
                    ||  Speed3 != Speedold3
                    || PositionL3 != PositionLold3
                    || PositionH3 != PositionHold3
                ){
                    controlold1 = control1;
                    statusold1 = status1;
                    Speedold1 = Speed1;
                    PositionLold1 = PositionL1;
                    PositionHold1 = PositionH1;

                    controlold2 = control2;
                    statusold2= status2;
                    Speedold2 = Speed2;
                    PositionLold2 = PositionL2;
                    PositionHold2 = PositionH2;

                    controlold3 = control3;
                    statusold3 = status3;
                    Speedold3 = Speed3;
                    PositionLold3 = PositionL3;
                    PositionHold3 = PositionH3;

                    motorController.insertMotorData(controlold1, statusold1, Speedold1, PositionLold1,PositionHold1,controlold2, statusold2, Speedold2, PositionLold2,PositionHold2,controlold3, statusold3, Speedold3, PositionLold3,PositionHold3);
                    // motorController.printMotorData();
                }
            
            
            }
        }));
    }
    void join(){
        exit_flag = false;
        motor_thread.join();
    }
private:
    std::shared_ptr<ModbusWrapper> modbusmotor;

    int16_t control1=0;
    int16_t status1=0;
    int16_t Speed1=0;
    int16_t PositionL1=0;
    int16_t PositionH1=0;

    int16_t control2=0;
    int16_t status2=0;
    int16_t Speed2=0;
    int16_t PositionL2=0;
    int16_t PositionH2=0;

    int16_t control3=0;
    int16_t status3=0;
    int16_t Speed3=0;
    int16_t PositionL3=0;
    int16_t PositionH3=0;


    int16_t controlold1=0;
    int16_t statusold1=0;
    int16_t Speedold1=0;
    int16_t PositionLold1=0;
    int16_t PositionHold1=0;

    int16_t controlold2=0;
    int16_t statusold2=0;
    int16_t Speedold2=0;
    int16_t PositionLold2=0;
    int16_t PositionHold2=0;

    int16_t controlold3=0;
    int16_t statusold3=0;
    int16_t Speedold3=0;
    int16_t PositionLold3=0;
    int16_t PositionHold3=0;

    MotorController motorController;

    std::thread  motor_thread;
    bool exit_flag{true};

};

