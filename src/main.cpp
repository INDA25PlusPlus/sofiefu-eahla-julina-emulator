#include <bits/stdc++.h>
using namespace std;

int main(){

    while(1){
        uint8_t operation_code = read_next_instruction(); // single byte 
        Instruction = decode_instruction(operation_code); // can use struct
        execute_instruction(instruction)
    }
}

