#include "crc32.h"
#include <unistd.h>
#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"
#include <stdio.h>
#include <iostream>
#include <cstdint>

#ifndef CALC_CRC32_H
#define CALC_CRC32_H


uint32_t calc_CRC32(MotorCmd cmd){
    uint8_t s[30];

    s[0] = 0xFE; // header 1
    s[1] = 0xEE; // header 2
    s[2] = static_cast<uint8_t> (cmd.id); // motor ID
    s[3] = 0x15;
    s[4] = 0x00; // ?
    s[5] = 0xFF; // 0xff
    s[6] = 0xFF;
    s[7] = 0x00;
    s[8] = 0x00; // 0
    s[9] = 0x00;
    s[10] = 0x20;
    s[11] = 0x42;
    s[12] = static_cast<uint8_t>(static_cast<int32_t>(cmd.tau * 256.0f) & 0xFF);; // target tau ?
    s[13] = 0x00;
    s[14] = 0xFF; // 0x7fff
    s[15] = 0x7F;
    s[16] = 0x80; // 0x7fe95c80 normally at 0x10
    s[17] = 0x5C; // 
    s[18] = 0xE9; // 
    s[19] = 0x7F; // 
    s[20] = static_cast<uint8_t>(static_cast<int32_t>(cmd.q * 256.0f) & 0xFF);; // target q ?
    s[21] = 0x00;
    s[22] = static_cast<uint8_t>(static_cast<int32_t>(cmd.dq * 256.0f) & 0xFF);; // target v ?
    s[23] = 0x04;
    s[24] = 0x05; // bVar1
    s[25] = 0x00;
    s[26] = 0x00;
    s[27] = 0x00;
    s[28] = 0x00;
    s[29] = 0x00;

    printf("Go1 payload is: ");
    for (int i=0; i<30; i++){
      printf("%02x", s[i]);
    }
    std::cout << std::endl;
    
    uint32_t* ptr_s ;
    ptr_s = (uint32_t *) &s;
    uint32_t crc = crc32_core(ptr_s, 7); // 7 lentgh = 28 bytes

    printf("computed CRC is: %02x ", (crc >> (8*0)) & 0xff);
    printf("%02x ", (crc >> (8*1)) & 0xff);
    printf("%02x ", (crc >> (8*2)) & 0xff);
    printf("%02x", (crc >> (8*3)) & 0xff);
    std::cout << std::endl;

    return crc; 
} 
#endif