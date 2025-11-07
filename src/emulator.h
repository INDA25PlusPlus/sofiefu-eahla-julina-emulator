
#pragma once
#include <vector>
#include <map>
#include <cstdint>
#include <string>
using namespace std;

struct Emulator
{   
    // register
    // in order B, C, D, E, H, L, (M), A
    enum RegisterIndex { // Dessa initialiseras med 0, 1, .., 7 "automatiskt"
      REG_B = 0,
      REG_C,
      REG_D,
      REG_E,
      REG_H,
      REG_L,
      REG_M, // minne vid H + L
      REG_A,
    };
    uint8_t registers[8];

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

    uint8_t flag_byte = 0;


    bool halted; // lägger till denna så att vi vet ifall emulateCycle() ska fortsätta köras

    uint8_t memory[65536]; // 65536 bytes enligt dokumentationen

    void initialize();
    void loadProgram(const char* filename);
    void emulateCycle();

    // split instruction checks
    void handleMisc(uint8_t opcode);
    void handleLoadStoreMove(uint8_t opcode);
    void handleArithmetic(uint8_t opcode);
    void handleBranchOrStack(uint8_t opcode);

    uint16_t pop16();
    uint8_t encode_flag_byte();
    void decode_flag_byte(uint8_t flag_byte);
    uint8_t checkParity(uint8_t byte);

    void set_flags(uint8_t result);
    void set_flags_before_add(uint8_t a, uint8_t b, uint8_t result);
    void set_flags_before_sub(uint8_t a, uint8_t b, uint8_t result);

    // instructions
    // Finns tex bara en unconditional JMP, men flera conditional mha flaggor, så najs att ha
    // som en metod
    void JMP();
    void CALL();

    void MOV(uint8_t opcode);
    int get_binary_value(uint8_t byte, int r, int l);
    void PUSH(uint8_t high, uint8_t low);
    void RST(uint8_t n);

    void printCPUstate();
    void printRegister(uint8_t value);
};

#define B registers[REG_B]
#define C registers[REG_C]
#define D registers[REG_D]
#define E registers[REG_E]
#define H registers[REG_H]
#define L registers[REG_L]
// #define M registers[REG_M]
#define A registers[REG_A]
