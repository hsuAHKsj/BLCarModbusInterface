#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <thread>
#include "modbus_wrapper.h"
#include "lightsql.h"
#include "common.h"




enum LightDescription {
    LightState=0
};


const std::string S_tate = "状态灯";


class Light {

public:
    Light(ModbusWrapper *modubs=nullptr):modbusptr(std::shared_ptr<ModbusWrapper>(modubs)),
        lightmanager(server, user, password, database)
    {
            

    }
    ~Light(){

    }

    void read_holding_register(const LightDescription &description);

    void start() {
        
        light_thread = std::move(std::thread([this](){
            while(exit_flag) {
                read_holding_register(LightState);
    

                if( State != Stateold){
                    Stateold = State;
                    
                    lightmanager.insertLightData(Stateold);
                    // lightmanager.printLightData();
                }
            
            
            }
        }));
    }
    void join(){
        exit_flag = false;
        light_thread.join();
    }
private:
    std::shared_ptr<ModbusWrapper> modbusptr;

    int16_t State=0;
    


    int16_t Stateold=0;
    

    LightManager lightmanager;

    std::thread  light_thread;
    bool exit_flag{true};

};