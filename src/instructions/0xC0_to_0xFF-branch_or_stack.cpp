#include "../emulator.h"
using namespace std;

void Emulator::handleBranchOrStack(uint8_t opcode) 
{
    switch (opcode)
    {
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
        
        case 0xC5: // PUSH B -- unconditional
            PUSH(registers[0], registers[1]);
            return;

        case 0xC6: // ADI
            // TODO
            return;

        case 0xC7: RST(0);  return; // RST n -- reset/restart

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
        
        // TODO 0xCB

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

        case 0xCF: RST(1); return;

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
            PUSH(registers[2], registers[3]);
            return;

        case 0xD6: // SUI d8 -- content of second byte of instruction is
            // subtracted from the content of the accumulator
            uint8_t data = memory[PC];
            PC++;
            uint16_t result = A - data; // needs to be stored in result to update CY flag

            // uppdatera flaggor
            flags.Z = ((result & 0xFF) == 0);
            flags.S = ((result & 0x80) != 0);
            flags.P = checkParity(result & 0xFF);
            flags.CY = (result > 0xFF);
            flags.AC = ((A & 0x0F) < (data & 0x0F));

            A = (uint8_t)(result & 0xFF);
            return;

        case 0xD7: RST(2); return;

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

        case 0xDF: RST(3); return;

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
            PUSH(registers[4], registers[5]);
            return;

        case 0xE6: // ANI d8
            // TODO
            return;

        case 0xE7: RST(4); return;

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

        case 0xEF: RST(5); return;

        case 0xF0: // RP -- return if positive
            if (!flags.S) {
                PC = pop16();
            }
            return;

        case 0xF1: // POP PSW
            flag_byte = memory[SP];
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

            flag_byte = encode_flag_byte();
            
            PUSH(A, flag_byte);
            return;

        case 0xF6: // ORI d8
            // TODO
            return;

        case 0xF7: RST(6); return;

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

        case 0xFF: RST(7); return;

        // TODO: Write all cases and implement them
    }
}
