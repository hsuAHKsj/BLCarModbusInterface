
#pragma once
#include "modbus.h"
#include <string>
#include <map>

typedef std::map<std::string, int16_t> Register;

class ModbusWrapper {
public:
    ModbusWrapper(const std::string &ip, int port);
    ~ModbusWrapper();

    bool connect();
    void close();

    void parse_config(const std::string CONFIG_CSV);
    int read_holding_register(const std::string &description, int16_t *value);
    int write_register(const std::string &description, int value);
    Register read_all_holding_registers(bool print); 
    int getaddress(std::string description){
        if(config.find(description) == config.end()) {
            printf("%s find failed\r\n",  description.c_str());
            return -1;
        }
        return config[description];
    }
	int read_all_holding_registers(int16_t address, int16_t amount, int16_t *buffer);
    modbus* mb_ptr;
private:
    std::map<std::string, int> config;
    
};
