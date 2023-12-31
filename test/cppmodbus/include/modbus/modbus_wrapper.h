
#pragma once
#include "modbus/modbus.h"
#include <string>
#include <map>

typedef std::map<std::string, uint16_t> Register;

class ModbusWrapper {
public:
    ModbusWrapper(const std::string &ip, int port);
    ~ModbusWrapper();

    bool connect();
    void close();

    void parse_config(const std::string CONFIG_CSV);
    int read_holding_register(const std::string &description, uint16_t *value);
    int write_register(const std::string &description, int value);
    Register read_all_holding_registers(bool print); 

    modbus* mb_ptr;
private:
    std::map<std::string, int> config;
    
};
