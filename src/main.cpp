
#include "emulator.h"
#include "iostream"
using namespace std;


int main(){
    Emulator cpu;
    cpu.initialize();
    cpu.loadProgram("examples/no-output-fib.bin");


    while(true){
        if (!cpu.halted) {
            cpu.emulateCycle();
        } else {
            // break, wait for interrupt, eller annat??
            break;
        }
    }

    return 0;
}
