#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include "cpu.h"

int main(int argc, char **argv)
{
    // Makes a new chip8 and loads in file
    C8 *chip8 = chip_8_init();
    
    FILE *f = fopen(argv[2], "rb");
    
    int option;
    while ((option = getopt(argc, argv, "dfh")) != -1){
        switch (option){
        case 'd':
            printf("DEBUG: Arg registered\n");

            if (f == NULL)
            {
                printf("ERROR: Couldn't open %s\n", argv[1]);
                exit(1);
            }
            disassemble_rom(chip8, f);
            break;
        case 'h':
            printf("Usage: emu -d <filename> | emu -f <filename>\n");
            break;
        case 'f':
            load_rom(chip8, f);
            break; 
        default:
            abort();

        }
    }
}
