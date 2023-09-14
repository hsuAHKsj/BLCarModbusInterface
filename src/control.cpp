#include "control.h"


std::atomic<bool>  Controller::alive(false);
std::mutex  Controller::mutex;
std::condition_variable  Controller::condition;

void Controller::run(){
        while (connectflag) {
            {
                if(!alive) {
                    continue;
                } 

                std::unique_lock<std::mutex> lock(mutex);
                // if (stopFlag) {
                //     break;
                // }

                // // 读取寄存器状态并进行存储
                // int registerValue = controller.readRegister();
                // // TODO: 存储寄存器状态的操作

                // // 设置三个电机的速度
                // motorController.setSpeed(1, registerValue);
                // motorController.setSpeed(2, registerValue * 2);
                // motorController.setSpeed(3, registerValue * 3);
                spdlog::debug("connect contorl thread");

                condition.wait_for(lock, std::chrono::seconds(1)); // 每秒执行一次

            }
        }
    } 



int Controller::get_battery_state(int start, int16_t *data_buffer){

    int index = modbusptr->getaddress(Battery_Voltage);
    index -=  start;
    if(index < 0 || index > amount) {
        spdlog::error("Battery_Voltage index not exist\r\n");
        return -1;
    }
    Voltage = data_buffer[index];
    spdlog::debug("index {} Voltage:{}\r\n", index, Voltage);
    index = modbusptr->getaddress(Battery_Current);
    index -=  start;

    if(index < 0 || index > amount) {
        spdlog::error("Battery_Current index not exist\r\n");
        return -1;
    }
    Current = data_buffer[index];

    index = modbusptr->getaddress(Battery_Soc);
    index -=  start;

    if(index < 0 || index > amount) {
        spdlog::error("Battery_Soc index not exist\r\n");
        return -1;
    }
    Soc = data_buffer[index];    
    spdlog::debug("index {} Soc:{}\r\n", index, Soc);

    index = modbusptr->getaddress(Battery_Temperature);
    index -=  start;

    if(index < 0 || index > amount) {
        spdlog::error("Battery_Temperature index not exist\r\n");
        return -1;
    }
    Temperature = data_buffer[index];

    index = modbusptr->getaddress(Battery_AlarmValue);
    index -=  start;

    if(index < 0 || index > amount) {
        spdlog::error("Battery_AlarmValue index not exist\r\n");
        return -1;
    }
    AlarmValue = data_buffer[index];
    return 0;
}


int Controller::get_motorcontroll_state(int start, int16_t *data_buffer, int motorclass){

    int index;
    if(motorclass == 1) {
        index = modbusptr->getaddress(control_Word1);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("control_Word1 index not exist\r\n");
            return -1;
        }
        control1 = data_buffer[index];
        
        index = modbusptr->getaddress(status_Word1);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("status_Word1 index not exist\r\n");
            return -1;
        }
        status1 = data_buffer[index];


        index = modbusptr->getaddress(current_Speed1);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_Speed1 index not exist\r\n");
            return -1;
        }
        Speed1 = data_buffer[index];

        index = modbusptr->getaddress(current_PositionL1);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionL1 index not exist\r\n");
            return -1;
        }
        PositionL1 = data_buffer[index];    


        index = modbusptr->getaddress(current_PositionH1);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionH1 index not exist\r\n");
            return -1;
        }
        PositionH1 = data_buffer[index];
    }else if (motorclass == 2) {

        index = modbusptr->getaddress(control_Word2);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("control_Word2 index not exist\r\n");
            return -1;
        }
        control2 = data_buffer[index];

        
        index = modbusptr->getaddress(status_Word2);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("status_Word2 index not exist\r\n");
            return -1;
        }
        status2 = data_buffer[index];

        index = modbusptr->getaddress(current_Speed2);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_Speed2 index not exist\r\n");
            return -1;
        }
        Speed2 = data_buffer[index];    


        index = modbusptr->getaddress(current_PositionL2);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionL2 index not exist\r\n");
            return -1;
        }
        PositionL2 = data_buffer[index];

        index = modbusptr->getaddress(current_PositionH2);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionH2 index not exist\r\n");
            return -1;
        }
        PositionH2 = data_buffer[index];
    }else {

        index = modbusptr->getaddress(control_Word3);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("control_Word3 index not exist\r\n");
            return -1;
        }
        control3 = data_buffer[index];

        index = modbusptr->getaddress(status_Word3);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("status_Word3 index not exist\r\n");
            return -1;
        }
        status3 = data_buffer[index];

        index = modbusptr->getaddress(current_Speed3);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_Speed3 index not exist\r\n");
            return -1;
        }
        Speed3 = data_buffer[index];    

        index = modbusptr->getaddress(current_PositionL3);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionL3 index not exist\r\n");
            return -1;
        }
        PositionL3 = data_buffer[index];

        index = modbusptr->getaddress(current_PositionH3);
        index -=  start;
        if(index < 0 || index > amount) {
            spdlog::error("current_PositionH3 index not exist\r\n");
            return -1;
        }
        PositionH3 = data_buffer[index];
    }
    return 0;
}
int Controller::get_car_state(int start, int16_t *data_buffer) {

    int index;
    index = modbusptr->getaddress(Auto_State);
    index -=  start;
    if(index < 0 || index > amount) {
        spdlog::error("Auto_State index not exist\r\n");
        return -1;
    }
    Astate = data_buffer[index];

    index = modbusptr->getaddress(Manual_State);
    index -=  start;
    if(index < 0 || index > amount) {
        spdlog::error("Manual_State index not exist\r\n");
        return -1;
    }

    Mstate = data_buffer[index];

    return 0;
} 





int Controller::read_all_holding_register(int start, int16_t *data_buffer) {
            
    int ret = 0;
    if(modbusptr == nullptr) {
        std::cout << "modbusptr == nullptr\r\n";
        return -1;
    }

    {
        std::unique_lock<std::mutex> lock(mutex);
        ret = modbusptr->read_all_holding_registers(start, 40, data_buffer);
    }
    if(ret != 0){
        spdlog::error("read_all_holding_registers failed\r\n");
        return ret;
    } 

    // ret = get_battery_state();
  
    // ret = get_motorcontroll_state();

    // ret = get_car_state();
    
    return ret;
}
