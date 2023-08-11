#include "music.h"
#include "log.h"
//DEFINE_DEBUG_LEVEL(DEBUG_LEVEL_INFO);




void Music::read_holding_register(const MusicDescription &description) {
            
    if(modbusptr == nullptr) {
        std::cout << "modbusptr == nullptr\r\n";
        return;
    }

    switch (description)
    {
    case MusicNumber/* constant-expression */:
        /* code */
        modbusptr->read_holding_register(Music_Number, &Number);
        INFO("Number: %d\r\n", Number);
        break;
    case MusicVolume:
        modbusptr->read_holding_register(Music_Volume, &Volume);
        INFO("Volume: %d\r\n", Volume);

        break;
    
    default:
        break;
    }
}