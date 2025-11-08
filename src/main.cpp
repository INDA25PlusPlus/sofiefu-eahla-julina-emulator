
#include "emulator.h"
#include "iostream"
using namespace std;

int main(){
    Emulator cpu;
    cpu.initialize();
    cpu.loadProgram("./8080-machine-code-examples/program.bin");

    while(true){
        cpu.printCPUstate();

        if (!cpu.halted) {
            cpu.emulateCycle();
        } else {
            // break, wait for interrupt, eller annat??
            break;
        }
    }

    return 0;
}
