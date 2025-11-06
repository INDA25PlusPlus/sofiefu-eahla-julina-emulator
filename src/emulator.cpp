
#include "emulator.h"
#include <cstring>
#include <fstream>
using namespace std;


void Emulator::initialize() { 

        A=B=C=D=E=H=L = 0; // TODO: ÄNDRA TILL LISTA?
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
    switch (opcode)
    {
        case 0x00: // NOP
            // no operation is performed
            return;

        case 0x76: // HLT
            // stops the processor from fetching and executing further instructions
            halted = true;
            return;

        
        // BRANCH GROUP

        case 0xC0: // RNZ -- return on no zero
            if (flags.Z == 0) { // if NOT zero
                // pop 16-bit return address from memory and return and assign PC to this.
                PC = pop16();
            }
            return;
            
        case 0xC1: // POP B //!!! CHANGE IF WE CHANGE REGISTERS TO LIST
            // pop two bytes from the stack into BC pair
            C = memory[SP]; // low byte
            B = memory[SP+1]; // high byte
            SP += 2;
            return;

        case 0xC2: // JNZ a16 -- jump on not zero
            // first low order address in memory[PC+1]
            // then high order address in memory[PC+2]
            if (flags.Z == 0) {
                JMP();
            } else {
                PC += 2; // skip this instruction
            }
            return;

        case 0xC3: // JMP a16 -- unconditional
            JMP();
            return;
        
        case 0xC4: // CNZ -- call if not zero
            if (flags.Z == 0) {
                CALL();
            } else {
                PC += 2; 
            }
            return;
        
        case 0xC5: // PUSH -- unconditional
            // TODO
            return;
        
        case 0xC6: // ADI
            // TODO
            return;

        case 0xC7: // RST -- reset/restart
            // TODO
            return;

        case 0xC8: // RZ -- return if zero
            if (flags.Z) {
                PC = pop16();
            }
            return;

        case 0xC9: // RET -- return unconditional
            PC = pop16();
            return;

        case 0xCA: // JZ a16 -- jump if zero
            if (flags.Z) {
                JMP();
            } else {
                PC += 2; // instruction ignored
            }
            return;

        case 0xCC: // CZ a16 -- call if zero
            if (flags.Z) {
                CALL();
            } else {
                PC += 2;
            }
            return;
        
        case 0xCD: // CALL a16
            CALL();
            return;
            
        case 0xCE: // ACI d6
            // TODO
            return;

        case 0xCF: // RST 1
            // TODO 
            return;

        case 0xD0: // RNC -- return on no carry
            if (!flags.CY) {
                PC = pop16();
            }
            return;
        
        case 0xD1: // POP D
            // TODO
            // pop two bytes from the stack into DE pair
            return;
        
        case 0xD2: // JNC -- jump on no carry
            if (!flags.CY) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xD3: // OUT d8
            // TODO
            return;

        case 0xD4: // CNC a16 -- call if no carry
            if (!flags.CY) {
                CALL();
            } else {
                PC += 2;
            }
            return;

        case 0xD5: // PUSH D
            // TODO
            return;

        case 0xD6: // SUI d8
            // TODO
            return;

        case 0xD7: // RST 2
            // TODO
            return;

        case 0xD8: // RC -- return if carry
            if (flags.CY) {
                PC = pop16();
            }
            return;

        // case 0xD9

        case 0xDA: //JC -- jump if carrry
            if (flags.CY) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xDB: // IN d8
            // TODO
            return;

        
            
        
        // TODO: Write all cases and implement them
        

    }

    switch (opcode & 0xC0) // compare first two bits
    {
        case 0x40:
            MOV(opcode);
            break;
        
        case 0x80: // 
            // handle_ALU(opcode);
            break;

        default:
            break;
    }
    
}


uint16_t Emulator::pop16() {
    uint8_t low = memory[SP];
    uint8_t high = memory[SP+1];
    SP += 2;
    return (high << 8) | low;
}

void Emulator::CALL() {
    uint8_t addr = (memory[PC + 1] << 8) | memory[PC];
            
    // push return address (PC + 2) onto stack
    uint8_t ret = PC + 2;
    SP -= 2;
    memory[SP] = ret & 0xFF; // low byte
    memory[SP - 2] = (ret >> 8) & 0xFF; // high byte

    SP -= 2;
    PC = addr;
}


void Emulator::JMP() {
    uint16_t addr = memory[PC] | (memory[PC+1] << 8);
    PC = addr;
}