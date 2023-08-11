#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <thread>
#include "modbus_wrapper.h"
#include "batterysql.h"
#include "common.h"


struct VoltageAlarm {
    
    uint8_t S_OneLevelHigh : 1; //bit0
    uint8_t S_TwoLevelHigh : 1;
    uint8_t S_OneLevelLow : 1;
    uint8_t S_TwoLevelLow : 1;
    uint8_t A_OneLevelHigh : 1;
    uint8_t A_TwoLevelHigh : 1;
    uint8_t A_OneLevelLow : 1;
    uint8_t A_TwoLevelLow : 1;
};


struct Charge_DisCharge_TemperatureAlarm {

    uint8_t C_OneLevelHigh : 1;//bit0
    uint8_t C_TwoLevelHigh : 1;
    uint8_t C_OneLevelLow : 1;
    uint8_t C_TwoLevelLow : 1;
    uint8_t D_OneLevelHigh : 1;
    uint8_t D_TwoLevelHigh : 1;
    uint8_t D_OneLevelLow : 1;
    uint8_t D_TwoLevelLow : 1;
};


struct Charge_DisCharge_OverFlowandSocAlarm {
    uint8_t CO_OneLevelHigh : 1;//bit0
    uint8_t CO_TwoLevelHigh : 1;
    uint8_t DO_OneLevelLow : 1;
    uint8_t DO_TwoLevelLow : 1;
    uint8_t SOC_OneLevelHigh : 1;
    uint8_t SOC_TwoLevelHigh : 1;
    uint8_t SOC_OneLevelLow : 1;
    uint8_t SOC_TwoLevelLow : 1;
};

struct Pressure_TemperatureDiffAlarm {

   uint8_t P_OneLevelLarge : 1;//bit0
   uint8_t P_TwoLevelLarge : 1;
   uint8_t T_OneLevelLarge : 1;
   uint8_t T_TwoLevelLarge : 1;
   uint8_t Resreve4 : 1;
   uint8_t Resreve5 : 1;
   uint8_t Resreve6 : 1;
   uint8_t Resreve7 : 1;
};



struct Charge_DisCharge_MOSAlarm {
    uint8_t C_OverTemperature : 1;//bit0
    uint8_t D_OverTemperature : 1;
    uint8_t C_TemperatureSensorFault : 1;
    uint8_t D_TemperatureSensorFault : 1;
    uint8_t C_AdhereFault : 1;
    uint8_t D_AdhereFault : 1;
    uint8_t C_TurnOffFault : 1;
    uint8_t D_TurnOffFault : 1;
};


struct FaultAlarm {
    int16_t AEEFault : 1;//bit0
    int16_t SingleCollectionOffline : 1;
    int16_t SingleTemperatureSensorFault : 1;
    int16_t EEPROMFault : 1;
    int16_t RTCFault : 1;
    int16_t PrechargeFailure : 1;
    int16_t VehicleCommunicationFault : 1;
    int16_t IntranetCommunicationModuleFault : 1;

    int16_t CurrentModuleFault : 1;//bit8
    int16_t InternalTotalPressureDetectionFault : 1;
    int16_t ShortProtectionFault : 1;
    int16_t LowVoltageNoChargeFault : 1;
    int16_t Resreve12 : 1;
    int16_t Resreve13 : 1;
    int16_t Resreve14 : 1;
    int16_t Resreve15 : 1;
};


enum BatteryDescription {
    BatteryVoltage = 0,
    BatteryCurrent,
    BatterySoc,
    BatteryTemperature,
    BatteryAlarmValue,
};


const std::string Battery_Voltage = "锂电池电压";
const std::string Battery_Current = "锂电池电流";
const std::string Battery_Soc = "锂电池SoC";
const std::string Battery_Temperature = "锂电池温度";
const std::string Battery_AlarmValue = "锂电池报警值";

class Battery {

public:
    Battery(ModbusWrapper *modubs=nullptr):modbusptr(std::shared_ptr<ModbusWrapper>(modubs)),
        batterymanager(server, user, password, database)
    {
            

    }
    ~Battery(){

    }

    void read_holding_register(const BatteryDescription &description);

    void start() {
        
        battery_thread = std::move(std::thread([this](){
            while(exit_flag) {
                read_holding_register(BatteryVoltage);
                read_holding_register(BatteryCurrent);
                read_holding_register(BatterySoc);
                read_holding_register(BatteryTemperature);
                read_holding_register(BatteryAlarmValue);

                if(    Voltage != Voltageold
                    || Current != Currentold
                    ||  Soc != Socold
                    || Temperature != Temperatureold
                    || AlarmValue != AlarmValueold
                ){
                    Voltageold = Voltage;
                    Currentold = Current;
                    Socold = Soc;
                    Temperatureold = Temperature;
                    AlarmValueold = AlarmValue;
                    batterymanager.insertBatteryData(Voltageold, Currentold, Socold, Temperature, AlarmValueold);
                    // batterymanager.printBatteryData();
                }
            
            
            }
        }));
    }
    void join(){
        exit_flag = false;
        battery_thread.join();
    }
private:
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

    BatteryManager batterymanager;

    std::thread  battery_thread;
    bool exit_flag{true};

};