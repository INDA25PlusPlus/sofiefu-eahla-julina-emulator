# 8080 Emulator Implemented in C++

To compile, run the following command in the project's root directory:

g++ -std=c++20 -o test $(find src -name "*.cpp")

The command creates an executable file named 'test' in the root directory. The file 'test' runs '/8080-machine-code-examples/program.bin' with this emulator and prints it's cpu state between each instruction. 

For 'program.bin', it will calculate fibonacci numbers - look for example at register B to see how far it's calculated.