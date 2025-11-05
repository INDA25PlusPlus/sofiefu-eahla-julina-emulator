
#include "emulator.h"
#include "iostream"
using namespace std;


int main(){
    Emulator cpu;
    cpu.initialize();
    cpu.loadProgram("exempel.bin");


    while(true){
        cpu.emulateCycle();
    }

    return 0;
}
