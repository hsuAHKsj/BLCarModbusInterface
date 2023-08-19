#pragma once

#include <iostream>
#include <atomic>
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <functional>
#include <nlohmann/json.hpp>

#include "common.h" 
#include "modbus_wrapper.h"


// 控制器

const std::string Battery_Voltage = "锂电池电压";
const std::string Battery_Current = "锂电池电流";
const std::string Battery_Soc = "锂电池SoC";
const std::string Battery_Temperature = "锂电池温度";
const std::string Battery_AlarmValue = "锂电池报警值";

const std::string Auto_State = "车体状态-自动";
const std::string Manual_State = "车体状态-手动";

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


const int EMERGENCY_STOP_FLAG = -2;
using json = nlohmann::json;

class Controller {
public:

    Controller(){

    }
    ~Controller(){


    }
    int readRegister(const std::string &description, int16_t value) {
       
        
        int ret;
        {
            std::unique_lock<std::mutex> lock(mutex);
            ret = modbusptr->read_holding_register(description, &value);

        }
        //std::cout << "Reading to register: " << value << std::endl;
        return ret;
    }

    int writeRegister(const std::string &description, int value) {
        int ret = 0;
        {
            std::unique_lock<std::mutex> lock(mutex);
            ret = modbusptr->write_register(description, value);
        }
        return ret;
        //std::cout << "Writing to register: " << value << std::endl;
    }
public:
   
    static int EMERGENCY_STOP(){
        int ret = 0;
        alive = false;
        return ret;
    }

    static int MOTOR_ENABLE(){
        int ret = 0;
        alive = true;
        return ret;
    }
public:

    std::string get_ip(){
        return m_ip;
    }

    int CONNECT(std::string ip){
        int ret = 0;

        connectflag = true;
        m_ip = ip;

        std::thread(std::bind(&Controller::run, this)).detach();

        modbusptr = std::make_shared<ModbusWrapper>("192.168.1.120", 502);
        std::string csv_data = "../data/read_modbus_config.csv";
        modbusptr->parse_config(csv_data);
        ret = modbusptr->connect();

        return ret;
    }
    int DISCONNECT(){
        int ret = 0;
        {
            modbusptr->close();
        }
        connectflag = false;
        return ret;
    }

    int SPEEDJ_LEFT_WHEEL_MOTOR(int speed){
        int ret = 0;
        if(!alive) {
            return EMERGENCY_STOP_FLAG;
        }
        ret = writeRegister(current_Speed1, speed);
        return ret;
    }

    int SPEEDJ_RIGHT_WHEEL_MOTOR(int speed){
        int ret = 0;
        if(!alive) {
            return EMERGENCY_STOP_FLAG;
        }
        ret = writeRegister(current_Speed2, speed);
        return ret;
    }

    int SPEEDJ_LIFTER_MOTOR(int speed) {
        int ret = 0;
        if(!alive) {
            return EMERGENCY_STOP_FLAG;
        }
        ret = writeRegister(current_Speed3, speed);
        return ret;    
    } 

    std::string GET_LEFT_MOMTOR_STATE(){
        int ret = 0;
        ret = read_all_holding_register();

        std::string val = {}; 
        if(ret == 0) {
            json temp;
            temp["control1"] = control1;
            temp["status1"] = status1;
            temp["Speed1"] = Speed1;
            temp["PositionL1"] = PositionL1;  
            temp["PositionH1"] = PositionH1;
          
            spdlog::debug("GET_LIFTER_MOMTOR_STATE {}", temp.dump());
            return temp.dump();
        }
        return val;
    }

    std::string GET_RIGHT_MOTOR_STATE(){
        int ret = 0;
        ret = read_all_holding_register();
        std::string val = {}; 
            if(ret == 0) {
            json temp;
            temp["control2"] = control2;
            temp["status2"] = status2;
            temp["Speed2"] = Speed2;
            temp["PositionL2"] = PositionL2;  
            temp["PositionH2"] = PositionH2;
          
            spdlog::debug("GET_RIGHT_MOTOR_STATE {}", temp.dump());
            return temp.dump();
        }
        return val;
    }

    std::string GET_LIFTER_MOMTOR_STATE(){
        int ret = 0;
        ret = read_all_holding_register();
        std::string val = {}; 
        if(ret == 0) {
            json temp;
            temp["control3"] = control3;
            temp["status3"] = status3;
            temp["Speed3"] = Speed3;
            temp["PositionL3"] = PositionL3;  
            temp["PositionH3"] = PositionH3;
          
            spdlog::debug("GET_LIFTER_MOMTOR_STATE {}", temp.dump());
            return temp.dump();
        }
        return val;
    }

    std::string GET_CAR_STATE(){
        int ret = 0;
        ret = read_all_holding_register();
        std::string val = {}; 
        if(ret == 0) {
           json temp;
           temp["Astate"] = Astate;
           temp["Mstate"] = Mstate;
        
           spdlog::debug("GET_CAR_STATE {}", temp.dump());
           return temp.dump();
        }
        return val;
    }

    std::string GET_BACTTERTY_STATE(){
        int ret = 0;
        ret = read_all_holding_register();
        std::string val = {}; 
        if(ret == 0) {
           json temp;
           temp["Current"] = Current;
           temp["Voltage"] = Voltage;
           temp["Soc"] = Soc;
           temp["Temperature"] = Temperature;
           temp["AlarmValue"] = AlarmValue;
           spdlog::debug("GET_BACTTERTY_STATE {}", temp.dump());
           return temp.dump();
        }
        return val;
    }
public:

    void run();   
    int read_all_holding_register();
    int get_motorcontroll_state();
    int get_battery_state();
    int get_car_state();

private:
    static std::atomic<bool> alive;
    static std::mutex mutex;
    static std::condition_variable condition;

    bool connectflag = false;
    std::string m_ip;

    std::shared_ptr<ModbusWrapper> modbusptr;


    
    int16_t Voltage=0;
    int16_t Current=0;
    int16_t Soc=0;
    int16_t Temperature=0;
    int16_t AlarmValue=0;
    int16_t Voltageold=0;
    int16_t Currentold=0;
    int16_t Socold=0;
    int16_t Temperatureold=0;
    int16_t AlarmValueold=0;



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

    int16_t Astate=0;
    int16_t Mstate=0;
    

};

