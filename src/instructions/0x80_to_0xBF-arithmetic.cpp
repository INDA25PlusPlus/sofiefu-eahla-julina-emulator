#include "../emulator.h"
#include <iostream>
using namespace std;

void Emulator::handleArithmetic(uint8_t opcode) 
{
    switch (opcode) 
    {
        // --- 0x8X ---

        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x87: {
            // add from register last 3 to A
            uint8_t reg = opcode & 0b111;
            uint8_t res = A + registers[reg];

            set_flags_before_add(A, registers[reg], res);

            A = res;
            return;
        }

        case 0x86: {
            // lower 3 110 , (A)...- (A) + ((H) (L))
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A + memory[memory_location];

            set_flags_before_add(A, memory[memory_location], res);

            A = res;
            return;
        }

        // case 0x87: // Fixed right above here!

        // 8x - 90 // ADD r (lower 3) to A
        case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8f: {
            // (Add Register with carry)
            // (A) ~ (A) + (r) + (CY)
            uint8_t reg = opcode & 0b111;
            uint8_t res = A + registers[reg] + flags.CY;

            set_flags_before_add(A, registers[reg], res); // works with and without carry

            A = res;
            return;
        }

        case 0x8e: {
            //
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A + memory[memory_location] + flags.CY;

            set_flags_before_add(A, memory[memory_location], res);

            A = res;
            return;
        }

        // case 0x8f: // Fixed right above here!

        // --- 0x9X ---

        // SUB

        case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x97: {
            // sub from register last 3 to A
            uint8_t reg = opcode & 0b111;
            uint8_t res = A - registers[reg];

            set_flags_before_sub(A, registers[reg], res);

            A = res;
            return;
        }

        case 0x96: {
            // lower 3 110 , (A)...- (A) - ((H) (L))
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A - memory[memory_location];

            set_flags_before_sub(A, memory[memory_location], res);

            A = res;
            return;
        }

        // SBB

        case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9f: {
            // (Sub Register with carry
            // (A) ~ (A) - (r) - (CY)
            uint8_t reg = opcode & 0b111;
            uint8_t res = A - registers[reg] - flags.CY;

            set_flags_before_sub(A, registers[reg], res); // works with and without carry

            A = res;
            return;
        }

        case 0x9e: {
            //
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A - memory[memory_location] - flags.CY;

            set_flags_before_sub(A, memory[memory_location], res);

            A = res;
            return;
        }

        // --- 0xAX ---

        // ANA (and)

        case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA7: {
            // AND Register
            uint8_t reg = opcode & 0b111;
            uint8_t res = A & registers[reg];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 1;

            A = res;
            return;
        }

        case 0xA6: {
            // AND memory
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A & memory[memory_location];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 1;

            A = res;
            return;
        }

        // XRA

        case 0xA8: case 0xA9: case 0xAa: case 0xAb: case 0xAc: case 0xAd: case 0xAf: {
            // XOR Register
            uint8_t reg = opcode & 0b111;
            uint8_t res = A ^ registers[reg];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 0;

            A = res;
            return;
        }

        case 0xAe: {
            // XOR memory
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A ^ memory[memory_location];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 0;

            A = res;
            return;
        }

        // --- 0xBX ---

        // ORA

        case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB7: {
            // OR Register
            uint8_t reg = opcode & 0b111;
            uint8_t res = A | registers[reg];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 0;

            A = res;
            return;
        }

        case 0xB6: {
            // OR memory
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A | memory[memory_location];

            set_flags(res);
            flags.CY = 0;
            flags.AC = 0;

            A = res;
            return;
        }

        // CMP

        case 0xB8: case 0xB9: case 0xBa: case 0xBb: case 0xBc: case 0xBd: case 0xBf: {
            // CMP Register
            uint8_t reg = opcode & 0b111;
            uint8_t res = A - registers[reg];

            set_flags(res);
            A < registers[reg] ? flags.CY = 1 : flags.CY = 0;
            flags.AC = ((A & 0xF) < ((registers[reg] & 0xF))); // check if borrow to lowest nibble

            return;
        }

        case 0xBe: {
            // CMP memory
            uint16_t memory_location = (H << 8) + L;
            uint8_t res = A - memory[memory_location];

            set_flags(res);
            A < memory[memory_location] ? flags.CY = 1 : flags.CY = 0;
            flags.AC = ((A & 0xF) < ((memory[memory_location] & 0xF))); // check if borrow to lowest nibble

            return;
        }

        default: {
            cout << "Error Misdirected Instruction in 0x40 to 0x7F, instruction: " << opcode << "\n";
            halted = true;
            return;
        }
    }
}
