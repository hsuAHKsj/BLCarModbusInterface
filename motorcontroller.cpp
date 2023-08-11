#include "motorcontroller.h"
#include "log.h"





void Motorcontrol::read_holding_register(const MotorDescription &description) {
            
    if(modbusmotor == nullptr) {
        std::cout << "modbusmotor == nullptr\r\n";
        return;
    }

    switch (description)
    {
    case controlWord1/* constant-expression */:
        /* code */
        modbusmotor->read_holding_register(control_Word1, &control1);
        INFO("ControlWord1: %d\r\n", control1);
        break;
    case statusWord1:
        modbusmotor->read_holding_register(status_Word1, &status1);
        INFO("StatusWord1: %d\r\n", status1);

        break;
    case currentSpeed1:
        modbusmotor->read_holding_register(current_Speed1, &Speed1);
        INFO("CurrentSpeed1: %d\r\n", Speed1);

        break;
    case currentPositionL1:
        modbusmotor->read_holding_register(current_PositionL1, &PositionL1);
        INFO("CurrentPositionL1: %d\r\n", PositionL1);

        break;
    case currentPositionH1:
        modbusmotor->read_holding_register(current_PositionH1, &PositionH1);
        INFO("CurrentPositionH1: %d\r\n", PositionH1);

        break;

    case controlWord2/* constant-expression */:
        /* code */
        modbusmotor->read_holding_register(control_Word2, &control2);
        INFO("ControlWord2: %d\r\n", control2);
        break;
    case statusWord2:
        modbusmotor->read_holding_register(status_Word2, &status2);
        INFO("StatusWord2: %d\r\n", status2);

        break;
    case currentSpeed2:
        modbusmotor->read_holding_register(current_Speed2, &Speed2);
        INFO("CurrentSpeed2: %d\r\n", Speed2);

        break;
    case currentPositionL2:
        modbusmotor->read_holding_register(current_PositionL2, &PositionL2);
        INFO("CurrentPositionL2: %d\r\n", PositionL2);

        break;
    case currentPositionH2:
        modbusmotor->read_holding_register(current_PositionH2, &PositionH2);
        INFO("CurrentPositionH2: %d\r\n", PositionH2);

        break;

    case controlWord3/* constant-expression */:
        /* code */
        modbusmotor->read_holding_register(control_Word3, &control3);
        INFO("ControlWord3: %d\r\n", control3);
        break;
    case statusWord3:
        modbusmotor->read_holding_register(status_Word3, &status3);
        INFO("StatusWord3: %d\r\n", status3);

        break;
    case currentSpeed3:
        modbusmotor->read_holding_register(current_Speed3, &Speed3);
        INFO("CurrentSpeed3: %d\r\n", Speed3);

        break;
    case currentPositionL3:
        modbusmotor->read_holding_register(current_PositionL3, &PositionL3);
        INFO("CurrentPositionL3: %d\r\n", PositionL3);

        break;
    case currentPositionH3:
        modbusmotor->read_holding_register(current_PositionH3, &PositionH3);
        INFO("CurrentPositionH3: %d\r\n", PositionH3);

        break;

    default:
        break;
    }
}