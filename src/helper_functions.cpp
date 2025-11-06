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

void Emulator::push(uint8_t high, uint8_t low){
    SP--;
    memory[SP] = high;
    SP--;
    memory[SP] = low;
}
