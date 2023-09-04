/* example.cpp
 *
 * Copyright (C) 20017-2021 Fanzhe Lyu <lvfanzhe@hotmail.com>, all rights reserved.
 *
 * modbuspp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "modbus/modbus.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    // create a modbus object
    modbus mb = modbus("192.168.1.120", 502);

    // set slave id
    mb.modbus_set_slave_id(1);

    // connect with the server
    mb.modbus_connect();

    // read holding registers           function 0x03
    int buffer_size = 30;
    int start_reg = 810;
    uint16_t read_holding_regs[buffer_size];
    mb.modbus_read_holding_registers(start_reg, buffer_size, read_holding_regs);

    for(int i = 0; i < buffer_size; i++)
        cout << "index " << start_reg+i << " = "<< static_cast<short>(read_holding_regs[i]) << endl;

    // write single reg                 function 0x06
    // mb.modbus_write_register(830, -2);
    mb.modbus_close();
    return 0;
}
