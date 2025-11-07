#include "../emulator.h"
#include <iostream>
using namespace std;

void Emulator::handleLoadStoreMove(uint8_t opcode) 
{
    if (opcode == 0x76)
    {
        // HLT
        // stops the processor from fetching and executing further instructions
        halted = true;
    }
    else if (0x40 <= opcode <= 0x7F)
    {
        MOV(opcode);
    }
    else
    {
        cout << "Error Misdirected Instruction in 0x40 to 0x7F, instruction: " << opcode << "\n";
    }

    return;
}
