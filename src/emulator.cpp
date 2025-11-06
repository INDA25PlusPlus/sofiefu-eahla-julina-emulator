
#include <vector>
using namespace std;

struct Emulator{   
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

    vector<uint8_t> memory;

    Emulator() : memory(65536) { // 65536 bytes enligt dokumentationen

        A=B=C=D=E=H=L = 0;
        SP=PC = 0;
        Z=S=P=CY=AC = false;
    }


};

