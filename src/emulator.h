
#include <vector>
using namespace std;

struct Emulator
{   
    // register
    uint8_t A, B, C, D, E, H, L;

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

    bool Z, S, P, CY, AC;

    uint8_t memory[65536];

    void initialize();
    void loadProgram(const char* filename);
    void emulateCycle();

};




