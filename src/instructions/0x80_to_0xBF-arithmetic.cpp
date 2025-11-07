#include "../emulator.h"
using namespace std;

void Emulator::handleAritmethic(uint8_t opcode) 
{
    switch (opcode) 
    {
        // --- 0x8X ---

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

        // --- 0x9X ---

        // --- 0xAX ---

        // --- 0xBX ---
    }
}
