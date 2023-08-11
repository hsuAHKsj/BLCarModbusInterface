#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <thread>
#include "modbus_wrapper.h"
#include "musicsql.h"
#include "common.h"




enum MusicDescription {
    MusicNumber=0,
    MusicVolume,
};


const std::string Music_Number = "声光接口-读取";
const std::string Music_Volume = "声光接口-写入";

class Music {

public:
    Music(ModbusWrapper *modubs=nullptr):modbusptr(std::shared_ptr<ModbusWrapper>(modubs)),
        musicmanager(server, user, password, database)
    {
            

    }
    ~Music(){

    }

    void read_holding_register(const MusicDescription &description);

    void start() {
        
        music_thread = std::move(std::thread([this](){
            while(exit_flag) {
                read_holding_register(MusicNumber);
                read_holding_register(MusicVolume);

                if(    Number != Numberold
                    || Volume != Volumeold){
                    Numberold = Number;
                    Volumeold = Volume;
                    
                    musicmanager.insertMusicData(Numberold,Volumeold);
                    // musicmanager.printMusicData();
                }
            
            
            }
        }));
    }
    void join(){
        exit_flag = false;
        music_thread.join();
    }
private:
    std::shared_ptr<ModbusWrapper> modbusptr;

    int16_t Number=0;
    int16_t Volume=0;
    

    int16_t Numberold=0;
    int16_t Volumeold=0;

    MusicManager musicmanager;

    std::thread  music_thread;
    bool exit_flag{true};

};