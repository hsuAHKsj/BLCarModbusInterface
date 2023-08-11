#include "light.h"
#include "log.h"
DEFINE_DEBUG_LEVEL(DEBUG_LEVEL_INFO);




void Light::read_holding_register(const LightDescription &description) {
            
    if(modbusptr == nullptr) {
        std::cout << "modbusptr == nullptr\r\n";
        return;
    }

    switch (description)
    {
    case LightState/* constant-expression */:
        /* code */
        modbusptr->read_holding_register(S_tate, &State);
        INFO("State: %d\r\n", State);
        break;
    
    default:
        break;
    }
}