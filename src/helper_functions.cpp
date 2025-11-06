#include "emulator.h"
using namespace std;

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
    memory[SP] = return_address & 0xF; // stores return_address in stack (in memory)
    memory[SP + 1] = (return_address >> 8); 
    PC = 8 * n;
}