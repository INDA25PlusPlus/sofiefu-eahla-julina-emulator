#include <bits/stdc++.h>
using namespace std;

int main(){

    while(1){
        uint8_t operation_code = read_next_instruction(); // single byte 
        Instruction = decode_instruction(operation_code); // can use struct
        execute_instruction(instruction)
    }
}

void MOV_r1_r2(char r1, char r2){ // move register r2 to r1
    // will need switch
    state.register[r1] = state.regiser[r2]; // note: we do not empty it
}

void MVI_r_data(char r, uint8_t data){ // move one byte to register r
    state.register[r] = data;
}

void MOV_r_M(char r){ // moves from memory pointed by register H,L to register r
    state.register[r] = state.memory[]
}