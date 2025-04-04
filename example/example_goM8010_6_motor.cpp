#include <unistd.h>
#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include "crc/crc32.h"
#include "crc/calculate_CRC.h"

int main() {

  SerialPort  serial("/dev/ttyUSB0");
  MotorCmd    cmd;
  MotorData   data;

  /*while(true) 
  {
    uint8_t s[30];

    s[0] = 0xFE; // header 1
    s[1] = 0xEE; // header 2
    s[2] = 0x00; // motor ID
    s[3] = 0x15;
    s[4] = 0x00; // ?
    s[5] = 0xFF; // 0xff
    s[6] = 0xFF;
    s[7] = 0x00;
    s[8] = 0x00; // 0
    s[9] = 0x00;
    s[10] = 0x20;
    s[11] = 0x42;
    s[12] = 0x10; // target tau ?
    s[13] = 0x00;
    s[14] = 0xFF; // 0x7fff
    s[15] = 0x7F;
    s[16] = 0x80; // 0x7fe95c80 normally at 0x10
    s[17] = 0x5C; // 
    s[18] = 0xE9; // 
    s[19] = 0x7F; // 
    s[20] = 0x14; // target q ?
    s[21] = 0x00;
    s[22] = 0x00; // target v ?
    s[23] = 0x04;
    s[24] = 0x05; // bVar1
    s[25] = 0x00;
    s[26] = 0x00;
    s[27] = 0x00;
    s[28] = 0x00;
    s[29] = 0x00;

    /*
    These are from decompiled Go2 basic_service,
    likely leftover from Go1/B1 arch, doesnt match exactly

    SetMotor_cmd[cmdStartAddr + 0] = 0xeefe
    SetMotor_cmd[cmdStartAddr + 2] = param_2 // motor id
    SetMotor_cmd[cmdStartAddr + 4] = cVar2
    SetMotor_cmd[cmdStartAddr + 5] = 0xff
    SetMotor_cmd[cmdStartAddr + 8] = 0
    SetMotor_cmd[cmdStartAddr + 0x10] = 0x7fe95c80
    SetMotor_cmd[cmdStartAddr + 0xc // 12] = (short)(int)((float)iVar9 * fVar16 * (1.0 / fVar11) * 256.0)
    SetMotor_cmd[cmdStartAddr + 0xe // ] = uVar4 = 0x7fff
    SetMotor_cmd[cmdStartAddr + 0x14] = (short)(int)((fVar13 / (fVar11 * fVar11)) * 0.03834952 * 2048.0);
    SetMotor_cmd[cmdStartAddr + 0x16] = (short)(int)((fVar12 / (fVar11 * fVar11)) * 100.0 * 1024.0);
    SetMotor_cmd[cmdStartAddr + 0x18] = bVar1
    SetMotor_cmd[cmdStartAddr + 0x1e] = uVar5 // computed CRC
    */


    cmd.motorType = MotorType::GO_M8010_6;
    data.motorType = MotorType::GO_M8010_6;
    cmd.mode = queryMotorMode(MotorType::GO_M8010_6,MotorMode::FOC);
    cmd.id   = 0;
    cmd.kp   = 0.0;
    cmd.kd   = 0.01;
    cmd.q    = 0.0;
    cmd.dq   = -6.28*queryGearRatio(MotorType::GO_M8010_6);
    cmd.tau  = 0.0;
    cmd.GO_M8010_6_motor_send_data.CRC32 = calc_CRC32(cmd);
    serial.sendRecv(&cmd,&data);

    std::cout <<  std::endl;
    std::cout <<  "motor.q: "    << data.q    <<  std::endl;
    std::cout <<  "motor.temp: "   << data.temp   <<  std::endl;
    std::cout <<  "motor.W: "      << data.dq      <<  std::endl;
    std::cout <<  "motor.merror: " << data.merror <<  std::endl;
    std::cout <<  std::endl;

    usleep(200);
  }
