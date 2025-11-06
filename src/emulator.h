
#pragma once
#include <vector>
#include <map>
using namespace std;

struct Emulator
{   
    // register
    vector<uint8_t> registers{8};

    // stack pointer och program counter
    uint16_t SP;
    uint16_t PC;

    // flags
    // | Flag | Name            |
    // | ---- | --------------- |
    // | Z    | Zero            |
    // | S    | Sign            |
    // | P    | Parity          |
    // | CY   | Carry           |
    // | AC   | Auxiliary Carry |

    struct Flags 
    {
        uint8_t Z; 
        uint8_t S;
        uint8_t P;
        uint8_t CY;
        uint8_t AC;
    };

    Flags flags; 


    bool halted; // lägger till denna så att vi vet ifall emulateCycle() ska fortsätta köras

    uint8_t memory[65536]; // 65536 bytes enligt dokumentationen

    void initialize();
    void loadProgram(const char* filename);
    void emulateCycle();
    uint16_t pop16();

    // instructions
    // Finns tex bara en unconditional JMP, men flera conditional mha flaggor, så najs att ha
    // som en metod
    void JMP();
    void CALL();

    void MOV(uint8_t opcode);
    int get_binary_value(uint8_t byte, int r, int l);
    void push(uint8_t high, uint8_t low);
};




