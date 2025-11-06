
#include "emulator.h"
#include <cstring>
#include <fstream>
using namespace std;


void Emulator::initialize() { 

        A=B=C=D=E=H=L = 0;
        SP=PC = 0;
        Z=S=P=CY=AC = false;
        memset(memory, 0, sizeof(memory));
    }

void Emulator::loadProgram(const char* filename) {
    ifstream file(filename, ios::binary);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read((char*)memory, size);

    file.close();
}


void Emulator::emulateCycle() {

    // i8080 Instruction Set: https://pastraiser.com/cpu/i8080/i8080_opcodes.html

    uint8_t opcode = memory[PC];

    // handle unique instructions
    switch (opcode)
    {
        case 0x00: // NOP
            // NOP()
            return;

        case 0x76:
            // HLT();
            return;

        case 0xC0:
            // RNZ()
            return;

        case 0xC1:
            // POP(opcode)
            return;

        case 0xC2:
            // JNZ(opcode)
            return;

        case 0xC3: 
            // JMP(opcode)
            return;
        
        case 0xC4:
            // CNZ(opcode)
            return;
        
        case 0xC5:
            // PUSH(opcode);
            return;
        
        case 0xC6:
            // ADI(opcode):
            return;

        case 0xC7:
            // RST(opcode);
            return;

        case 0xC8:
            // RZ();
            return;

        case 0xC9:
            // RET(
            return;

        case 0xCA:
            // JZ(opcode)
        
        // TODO: Write all cases and implement them
        

    }

    switch (opcode & 0xC0) // compare first two bits
    {
        case 0x40:
            // handle_MOV(opcode);
            break;
        
        case 0x80: // 
            // handle_ALU(opcode);
            break;

        default:
            break;
    }
    
}
