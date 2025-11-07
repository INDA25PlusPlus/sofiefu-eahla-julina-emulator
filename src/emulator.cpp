#include "emulator.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
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
    if (0x00 <= opcode && opcode <= 0x3F) handleMisc(opcode);
    else if (0x40 <= opcode && opcode <= 0x7F) handleLoadStoreMove(opcode);
    else if (0x80 <= opcode && opcode <= 0xBF) handleArithmetic(opcode);
    else if (0xC0 <= opcode && opcode <= 0xFF) handleBranchOrStack(opcode);
    else 
    {
        cout << "Error Invalid opcode. opcode : " << opcode << "\n";
    }
}

void Emulator::printCPUstate() {

    // printa register

    cout << "REGISTERS\n";
    printRegister("A", A);
    printRegister("B", B);
    printRegister("C", C);
    printRegister("D", D);
    printRegister("E", E);
    printRegister("H", H);
    printRegister("L", L);
    

    cout << "\n\n";

    // printa flaggor
    
    cout << "FLAGS\n";
    cout << "Z:" << flags.Z << " ";
    cout << "S:" << flags.S << " ";
    cout << "P:" << flags.P << " ";
    cout << "AC:" << flags.AC << " ";
    cout << "CY:" << flags.CY;

    cout << "\n\n";

    // printa minne

   // cout << "MEMORY\n";
    cout << "PC: " << PC << " " << "SP: " << SP << "\n";
    // for (int i = 0; i < 16; i ++) {

    //     for (int j =0; j<16;j++) {

    //         cout << memory[i*16 + j] << " ";
    //     }
    //     cout << "\n";
    // }

    


}

void Emulator::printRegister(const std::string& name, uint8_t value) {
    std::cout << name << ": 0x"
              << std::hex 
              << std::uppercase 
              << std::setw(2) 
              << std::setfill('0') 
              << static_cast<int>(value) 
              << std::dec 
              << "\n";
}