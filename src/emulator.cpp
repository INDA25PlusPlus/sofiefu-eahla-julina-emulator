
#include "emulator.h"
#include <cstring>
#include <fstream>
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
    switch (opcode)
    {
        case 0x00: // NOP
            // no operation is performed
            return;

        case 0x76: // HLT
            // stops the processor from fetching and executing further instructions
            halted = true;
            return;
        

        // 0x80 - 0xC0 // ARITHMETIC INSTRUCTIONS

        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x87:
            // add from register last 3 to A
            uint8_t reg = opcode & 0b111;
            A = A + registers[reg];
            return;
        
        case 0x86:
            // lower 3 110 , (A)...- (A) + ((H) (L))
            //
            return;
        
        // case 0x87: // Fixed right above here!

        // 8x - 90 // ADD r (lower 3) to A
        case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8f:
            // (Add Register with carry)
            // (A) ~ (A) + (r) + (CY)
            uint8_t reg = opcode & 0b111;
            A = A + registers[reg] + flags.CY;
            return;
        
        case 0x8e:
            //
            return;

        // case 0x8f: // Fixed right above here!

        // 

        
        // BRANCH GROUP

        case 0xC0: // RNZ -- return on no zero
            if (flags.Z == 0) { // if NOT zero
                // pop 16-bit return address from memory and return and assign PC to this.
                PC = pop16();
            }
            return;
            
        case 0xC1: // POP B //!!! CHANGE IF WE CHANGE REGISTERS TO LIST
            // TODO: pop two bytes from the stack into BC pair
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
            push(registers[0], registers[1]);
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
            // pop two bytes from the stack into DE pair
            E = memory[PC]; // low byte
            D = memory[PC + 1]; // high byte
            PC += 2;
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
            push(registers[2], registers[3]);
            break;

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

        case 0xDC: // CC a16 -- call if carry
            if (flags.CY) {
                CALL();
            } else {
                PC += 2;
            }
            return;

        // case 0xDD

        case 0xDE: // SBI d8
            // TODO
            break;

        case 0xDF: // RST 3
            // TODO
            break;

        case 0xE0: // RPO -- return if parity odd
            if (!flags.P) {
                PC = pop16();
            }
            return;

        case 0xE1: // POP H
            L = memory[PC];
            H = memory[PC+1];
            PC += 2;
            return;

        case 0xE2: // JPO -- jump if parity odd
            if (!flags.P) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xE3: // XTHL
            // TODO
            return;

        case 0xE4: // CPO - call if parity odd
            if (!flags.P) {
                CALL();
            } else {
                PC += 2;
            }
        
        case 0xE5: // PUSH H
            push(registers[4], registers[5]);
            break;

        case 0xE6: // ANI d8
            // TODO
            return;

        case 0xE7: // RST 4
            // TODO 
            return;

        case 0xE8: // RPe -- return if parity even
            if (flags.P) {
                PC = pop16();
            }
            return;


        case 0xE9: // PCHL
            // TODO
            return;

        
        case 0xEA: // JPE -- jump if parity even
            if (flags.P) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xEB: //XCHG
            // TODO
            return;

        case 0xEC: // CPE -- call if parity even
            if (flags.P) {
                CALL();
            }
            return;

        // case 0xED

        case 0xEE: // XRI
            // TODO
            return;

        case 0xEF:  // RST 5
            // TODO
            return;

        case 0xF0: // RP -- return if positive
            if (!flags.S) {
                PC = pop16();
            }
            return;

        case 0xF1: // POP PSW
            int8_t flag_byte = memory[SP];
            A = memory[SP+1];

            decode_flag_byte(flag_byte);
            
            SP += 2;
            return;

        case 0xF2: // JP -- jump if positive
            if (!flags.S) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xF3: // DI
            // TODO
            return;

        case 0xF4: // CP -- call if positive
            if (!flags.S) {
                CALL();
            } else {
                PC += 2;
            }
            return;

        case 0xF5: // PUSH PSW
            // TODO
            return;

        case 0xF6: // ORI d8
            // TODO
            return;

        case 0xF7: // RST 6
            // TODO
            return;

        case 0xF8: // RM -- return if minus
            if (flags.S) {
                PC = pop16();
            }
            return;

        case 0xF9: // SPHL
            // TODO
            return;

        case 0xFA: // JM -- jump if minus
            if (flags.S) {
                JMP();
            } else {
                PC += 2;
            }
            return;

        case 0xFB: // EI
            // TODO
            return;

        case 0xFC: // CM -- call if minus
            if (flags.S) {
                CALL();
            } else {
                PC += 2;
            }
            return;

        // case 0xFD

        case 0xFE: // CPI d8
            // TODO
            return;

        case 0xFF: // RST 7
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

uint8_t Emulator::encode_flag_byte() {

    // flag byte format: S Z 1 AC 0 P 1 CY

    uint8_t flag_byte = 0;

    flag_byte |= (flags.S << 7);
    flag_byte |= (flags.Z << 6);
    flag_byte |= (1 << 5);
    flag_byte |= (flags.AC << 4);
    flag_byte |= (flags.P << 2);
    flag_byte |= (1 << 1);
    flag_byte |= (flags.CY << 0);

    return flag_byte;

}

void Emulator::decode_flag_byte(uint8_t flag_byte) {

    flags.S = (flag_byte >> 7) & 1;
    flags.Z = (flag_byte >> 6) & 1;
    flags.AC = (flag_byte >> 4) & 1;
    flags.P = (flag_byte >> 2) & 1;
    flags.CY = (flag_byte >> 0) & 1;

}


