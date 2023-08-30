#include "modbus/modbus_wrapper.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    // create a modbus object
    ModbusWrapper mbw("192.168.1.120", 502);
    const std::string csv_data = "../config/read_modbus_config.csv";
    mbw.parse_config(csv_data); 
    mbw.connect();

    uint16_t read_holding_regs[1];
    mbw.read_all_holding_registers(true);

    // write single reg                 function 0x06
    mbw.write_register("举升电机使能-控制字", -2);

    mbw.close();
    return 0;
}