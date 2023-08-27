// modbus_wrapper.cpp
#include "modbus_wrapper.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "common.h"
ModbusWrapper::ModbusWrapper(const std::string &ip, int port) {    
    mb_ptr = new modbus(ip, port);
}

std::string read_csv_file(const std::string &file_path) {
    std::ifstream file(file_path);
    std::string content;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << "cfg :\r\n " << line << "\r\n";
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << file_path << std::endl;
    }

    return content;
}


void ModbusWrapper::parse_config(const std::string csv_data)
{
    std::map<std::string, int> config_map;
    std::string data = read_csv_file(csv_data); 
    std::cout << "data " << std::endl;
    std::cout << data << std::endl;
    
    std::istringstream ss(data);
    std::string line;
    std::getline(ss, line);
    

    while (std::getline(ss, line)) {
        std::istringstream line_stream(line);
        std::string item;
        std::vector<std::string> items;

        while (std::getline(line_stream, item, ',')) {
            items.push_back(item);
        }

        if (items.size() == 3) {
            int address = std::stoi(items[0]);
            std::string description = items[1];
            config_map[description] = address;
        }
    }

    config = config_map;
}



ModbusWrapper::~ModbusWrapper() {
    close();
}

int ModbusWrapper::connect() {
    
    if(mb_ptr->modbus_connect()){
        return 0;
    }

    return -1;
}

void ModbusWrapper::close() {
    mb_ptr->modbus_close();
}

int ModbusWrapper::read_holding_register(const std::string &description, int16_t *value) {
    auto it = config.find(description);

    if (it != config.end()) {
        int address = it->second;
        // std::cout << "address: " << description << " int : " << address << " == ";
        return mb_ptr->modbus_read_holding_registers(address, 1, value);
    }
    return -1;
}

int ModbusWrapper::write_register(const std::string &description, int value) {
    auto it = config.find(description);
    if (it != config.end()) {
    int address = it->second;
    return mb_ptr->modbus_write_register(address, value);
    }
    return -1;
}

Register ModbusWrapper::read_all_holding_registers(bool print) {
    Register result;
    for (const auto &item : config) {
        int16_t value = 0;
        if (read_holding_register(item.first, &value) >= 0) {
            result[item.first] = value;
        }
    }

    if (print)
    {
        for (const auto &item : result) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }


    return result;
}

int ModbusWrapper::read_all_holding_registers(int16_t address, int16_t amount, int16_t *buffer){
	return  mb_ptr->modbus_read_holding_registers(address, amount, buffer);

}


