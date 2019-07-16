#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
#include "disassembler.h"
 
 int main(int argc, char **argv)
{
    // Makes a new chip8 and loads in file 
    C8* chip8 = chip_8_init();
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        printf("error: Couldn't open %s\n", argv[1]);
        exit(1);
    }
    
    
    disassemble_rom(chip8, f); 
    load_rom(chip8,f); 
    return 0;
} 