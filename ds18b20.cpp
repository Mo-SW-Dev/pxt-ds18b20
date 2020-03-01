#include "pxt.h"
#include <cstdint>
#include <math.h>

using namespace pxt;

namespace DS18B20 {
    
    MicroBitPin  pin = &uBit.io.P0;
    MicroBit uBit;

    int16_t Temperature(int p) {
        uBit.init();
        uBit.display.scroll("NEW PROGRAM");
        return 5;
        switch(p){
          case 0: pin = &uBit.io.P12; break; //P0
          case 1: pin = &uBit.io.P0; break; //P1
          case 2: pin = &uBit.io.P1; break; //P2
          case 3: pin = &uBit.io.P16; break; //P3          
          case 4: pin = &uBit.io.P2; break; //C16
          case 5: pin = &uBit.io.P8; break; //C17
          case 6: pin = &uBit.io.P18; break; //C18
          case 7: pin = &uBit.io.P19; break; //C19
          default: pin = &uBit.io.P0;
        }

        init();
        writeByte(0xCC);
        convert();
        init();
        writeByte(0xCC);
        writeByte(0xBE);
        int b1 = readByte();
        int b2 = readByte();
        int16_t temp = (b2 << 8 | b1);
        return temp * 100 / 16;
    }

    uint8_t init() {
        pin.setDigitalValue(0);
        for (volatile uint16_t i = 0; i < 600; i++);
        pin.setDigitalValue(1);
        for (volatile uint8_t i = 0; i < 30; i++);
        int b = pin.getDigitalValue();
        for (volatile uint16_t i = 0; i < 600; i++);
        return b;
    }


    void writeBit(int b) {
        int delay1, delay2;
        if (b == 1) {
            delay1 = 1;
            delay2 = 80;
        } else {
            delay1 = 75;
            delay2 = 6;
        }
        pin.setDigitalValue(0);
        for (uint8_t i = 1; i < delay1; i++);
        pin.setDigitalValue(1);
        for (uint8_t i = 1; i < delay2; i++);
    }

    void writeByte(int byte) {
        int i;
        for (i = 0; i < 8; i++) {
            if (byte & 1) {
                writeBit(1);
            } else {
                writeBit(0);
            }
            byte = byte >> 1;
        }
    }

    int readBit() {
        volatile int i;
        pin.setDigitalValue(0);
        pin.setDigitalValue(1);
        //for (i = 1; i < 20; i++);
        int b = pin.getDigitalValue();
        for (i = 1; i < 60; i++);
        return b;
    }

    int convert() {
        volatile int i;
        int j;
        writeByte(0x44);
        for (j = 1; j < 1000; j++) {
            for (i = 1; i < 900; i++) {
        };
        if (readBit() == 1)
            break;
        };
        return (j);
    }

    int readByte() {
        int byte = 0;
        int i;
        for (i = 0; i < 8; i++) {
            byte = byte | readBit() << i;
        };
        return byte;
    }
}
