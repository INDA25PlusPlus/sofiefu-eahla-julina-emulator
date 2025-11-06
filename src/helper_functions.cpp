#include "emulator.h"
#include <cstdint>
using namespace std;

void Emulator::MOV(uint8_t opcode){
    int start = get_binary_value(opcode, 2, 0), dest=get_binary_value(opcode, 5, 3);

    if(start==6){ // MOV r, M - to move content of message[H+L] to register r
        uint16_t pointer = ((uint16_t)registers[4] << 8) | registers[5];
        registers[dest] = memory[pointer];
    }
    else if(dest==6){ // MOV M, r
        uint16_t pointer = ((uint16_t)registers[4] << 8) | registers[5];
        memory[pointer] = registers[start];
    }
    else{ // MOV r1, r2
        registers[dest] = registers[start];
    }
} 

int Emulator::get_binary_value(uint8_t byte, int r, int l){
    int start = l;

    int mask = 0;
    for(int i=0; i<(r-l+1); i++){
        mask |= (1<<i);
    }
    return (byte>>start) & mask;
}

void Emulator::PUSH(uint8_t high, uint8_t low){
    SP--;
    memory[SP] = high;
    SP--;
    memory[SP] = low;
}

void Emulator::RST(uint8_t n){
    uint16_t return_address = PC;
    SP -= 2; // push things to stack, message address is two bytes
    memory[SP] = return_address & 0xFF; // stores return_address in stack (in memory)
    memory[SP + 1] = (return_address >> 8); 
    PC = 8 * n;
}