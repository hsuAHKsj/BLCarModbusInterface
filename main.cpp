// create a modbus object
#include "modbus_wrapper.h"
#include "battery.h"
#include "batterysql.h"
#include "motorcontroller.h"
#include "motorcontrollersql.h"
#include "lightsql.h"
#include "light.h"
#include "carstatesql.h"
#include "carstate.h"
#include "musicsql.h"
#include "music.h"

// static const char* server = "localhost";
// static const char* user = "root";
// static const char* password = "Binglin@123";
// static const char* database = "car";
int main()
{
     static const char* server = "localhost";
     static const char* user = "root";
     static const char* password = "Binglin@123";
     static const char* database = "car";
     ModbusWrapper *modbusPtr = new ModbusWrapper("192.168.1.120", 502);
     std::string csv_data = "../read_modbus_config.csv";
     modbusPtr->parse_config(csv_data);
     modbusPtr->connect();

     
     Battery m_battery(modbusPtr);
     m_battery.start();

   
    //  Motorcontrol m_motorcontrol(modbusPtr);
    //  m_motorcontrol.start();

    //  Light m_light(modbusPtr);
    //  m_light.start();

    //  Carstate m_carstate(modbusPtr);
    //  m_carstate.start();

    //  Music m_music(modbusPtr);
    //  m_music.start();

    while (1)
    {
        sleep(1);
    }
    
}
