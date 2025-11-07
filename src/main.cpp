
#include "emulator.h"
#include "iostream"
using namespace std;


int main(){
    Emulator cpu;
    cpu.initialize();
    cpu.loadProgram("examples/no-output-fib.bin");


    while(true){
        cpu.printCPUstate();
        if (!cpu.halted) {
            cpu.emulateCycle();
        } else {
            cpu.printCPUstate();
            break;
        }
    }

    return 0;
}
