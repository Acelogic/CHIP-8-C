#include <stdio.h>
#include <stdint.h>

typedef struct cpu{
    FILE * game;
    uint16_t opcode;
    uint8_t memory[4096];
    uint8_t V[0x10];
    uint16_t I;
    uint16_t pc;
    uint8_t graphics[64 * 32];
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t stack[0x10];
    uint16_t sp;
    uint8_t key[0x10];
} C8;
 