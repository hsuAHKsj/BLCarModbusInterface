#include "battery.h"
#include "log.h"
//DEFINE_DEBUG_LEVEL(DEBUG_LEVEL_INFO);




void Battery::read_holding_register(const BatteryDescription &description) {
            
    if(modbusptr == nullptr) {
        std::cout << "modbusptr == nullptr\r\n";
        return;
    }

    switch (description)
    {
    case BatteryVoltage/* constant-expression */:
        /* code */
        modbusptr->read_holding_register(Battery_Voltage, &Voltage);
        INFO("Voltage: %d\r\n", Voltage);
        break;
    case BatteryCurrent:
        modbusptr->read_holding_register(Battery_Current, &Current);
        INFO("Current: %d\r\n", Current);

        break;
    case BatterySoc:
        modbusptr->read_holding_register(Battery_Soc, &Soc);
        INFO("Soc: %d\r\n", Soc);

        break;
    case BatteryTemperature:
        modbusptr->read_holding_register(Battery_Temperature, &Temperature);
        INFO("Temperature: %d\r\n", Temperature);

        break;
    case BatteryAlarmValue:
        modbusptr->read_holding_register(Battery_AlarmValue, &AlarmValue);
        INFO("AlarmValue: %d\r\n", AlarmValue);

        break;
    default:
        break;
    }
}