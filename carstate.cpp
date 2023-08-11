#include "carstate.h"
#include "log.h"
//DEFINE_DEBUG_LEVEL(DEBUG_LEVEL_INFO);




void Carstate::read_holding_register(const CarstateDescription &description) {
            
    if(modbusptr == nullptr) {
        std::cout << "modbusptr == nullptr\r\n";
        return;
    }

    switch (description)
    {
    case AutoState/* constant-expression */:
        /* code */
        modbusptr->read_holding_register(Auto_State, &Astate);
        INFO("Astate: %d\r\n", Astate);
        break;
    case ManualState:
        modbusptr->read_holding_register(Manual_State, &Mstate);
        INFO("Mstate: %d\r\n", Mstate);

        break;
    
    default:
        break;
    }
}