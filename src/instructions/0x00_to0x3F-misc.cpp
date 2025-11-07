#include "../emulator.h"
using namespace std;

void Emulator::handleMisc(uint8_t opcode) 
{    
    switch (opcode)
    {
        // --- 0x0X ---

        case 0x00: // NOP
            // no operation is performed
            return;
        
        // --- 0x1X ---

        // --- 0x2X ---

        // --- 0x3X ---
    }
}
