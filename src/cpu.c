#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define memsize 4096

typedef struct cpu{
    FILE * game;
     
    unsigned short opcode;
    unsigned char memory[memsize];
    unsigned char V[0x10];
    unsigned short I;
    unsigned short pc;
    unsigned char graphics[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[0x10];
    unsigned short sp;
    unsigned char key[0x10];
} C8;
 