#include "emulator.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

void Emulator::initialize() { 

        std::fill(registers, registers + 8, 0);

        PC = 0;
        SP = 0xFFFF; // stack grows downward
        flags.Z  = 0;
        flags.S  = 0;
        flags.P  = 0;
        flags.CY = 0;
        flags.AC = 0;
        halted = false;
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
    // increment counter - now it points to the first operand of multi-byte instructions
    // or on the next instruction
    PC++;

    // handle unique instructions
    if (0x00 <= opcode <= 0x3F) handleMisc(opcode);
    else if (0x40 <= opcode <= 0x7F) handleLoadStoreMove(opcode);
    else if (0x80 <= opcode <= 0xBF) handleAritmethic(opcode);
    else if (0xC0 <= opcode <= 0xFF) handleBranchOrStack(opcode);
    else 
    {
        cout << "Error Invalid opcode. opcode : " << opcode << "\n";
    }
}
