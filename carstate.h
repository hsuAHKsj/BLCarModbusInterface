#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <thread>
#include "modbus_wrapper.h"
#include "carstatesql.h"
#include "common.h"





enum CarstateDescription {
    AutoState = 0,
    ManualState,
};


const std::string Auto_State = "车体状态-自动";
const std::string Manual_State = "车体状态-手动";


class Carstate {

public:
    Carstate(ModbusWrapper *modubs=nullptr):modbusptr(std::shared_ptr<ModbusWrapper>(modubs)),
        carstatemanager(server, user, password, database)
    {
            

    }
    ~Carstate(){

    }

    void read_holding_register(const CarstateDescription &description);

    void start() {
        
        carstate_thread = std::move(std::thread([this](){
            while(exit_flag) {
                read_holding_register(AutoState);
                read_holding_register(ManualState);
                

                if(    Astate != Astateold
                    || Mstate != Mstateold
                    
                ){
                    Astateold = Astate;
                    Mstateold = Mstate;
                    
                    carstatemanager.insertCarstateData(Astateold,Mstateold);
                    // carstatemanager.printCarstateData();
                }
            
            
            }
        }));
    }
    void join(){
        exit_flag = false;
        carstate_thread.join();
    }
private:
    std::shared_ptr<ModbusWrapper> modbusptr;

    int16_t Astate=0;
    int16_t Mstate=0;
    


    int16_t Astateold=0;
    int16_t Mstateold=0;
    

    CarstateManager carstatemanager;

    std::thread  carstate_thread;
    bool exit_flag{true};

};