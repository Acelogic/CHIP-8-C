#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include "cpu.h"
#include "disassembler.h"
int main(int argc, char const *argv[])
{
 C8* chip8 = load_rom(**argv); 
 disassemble(chip8, pc_read(chip8)); 
 return 0;  
}

