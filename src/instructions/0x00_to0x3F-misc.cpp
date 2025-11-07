#include "emulator.h"
#include <iostream>
using namespace std;

void Emulator::handleMisc(uint8_t opcode) 
{    
    switch (opcode)
    {
        // NOP

        case 0x00: case 0x10: case 0x20: case 0x30: {
            // no operation is performed
            return;
        }

        // LXI

        case 0x01: case 0x11: case 0x21: case 0x31: {
            // TODO
            return;
        }
        
        // STAX B, STAX D, SHLD, STA

        case 0x02: {
            // TODO
            return;
        }

        case 0x12: {
            // TODO
            return;
        }

        case 0x22: {
            // TODO
            return;
        }

        case 0x32: {
            // TODO
            return;
        }

        // INX B, D, H, SP

        case 0x03: case 0x13: case 0x23: case 0x33: {
            // TODO
            return;
        }

        // INR

        case 0x04: case 0x14: case 0x24: case 0x34: {
            // TODO
            return;
        }

        // DCR
        
        case 0x05: case 0x15: case 0x25: case 0x35: {
            // TODO
            return;
        }

        // MVI
        
        case 0x06: case 0x16: case 0x26: case 0x36: {
            // TODO
            return;
        }

        // RLC, RAL, DAA, STC
        
        case 0x07: case 0x17: case 0x27: case 0x37: {
            // TODO
            return;
        }

        // NOP

        case 0x08: case 0x18: case 0x28: case 0x38: {
            // no operation is performed
            return;
        }

        // DAD

        case 0x09: case 0x19: case 0x29: case 0x39: {
            // TODO
            return;
        }

        // LDAX B, LDAX D, LHLD, LDA

        case 0x0a: case 0x1a: case 0x2a: case 0x3a: {
            // TODO
            return;
        }

        // DCX

        case 0x0b: case 0x1b: case 0x2b: case 0x3b: {
            // TODO
            return;
        }

        // INR

        case 0x0C: case 0x1C: case 0x2C: case 0x3C: {
            // TODO
            return;
        }

        // DCR

        case 0x0D: case 0x1D: case 0x2D: case 0x3D: {
            // TODO
            return;
        }

        // MVI

        case 0x0E: case 0x1E: case 0x2E: case 0x3E: {
            // TODO
            return;
        }

        // RRC

        case 0x0F: case 0x1F: case 0x2F: case 0x3F: {
            // TODO
            return;
        }

        default: {
            cout << "Error Misdirected Instruction in 0x00 to 0x3F, instruction: " << opcode << "\n";
        }
    }
}
