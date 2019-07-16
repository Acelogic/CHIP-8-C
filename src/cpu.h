#include <stdio.h>
#include <stdint.h>



#define MEM_SIZE      4096
#define BYTES_PER_CHAR 5
#define CHARSET_SIZE  80
#define CHARSET_START 0x050
#define CHARSET_END   0x0A0
#define PROGRAM_START 0x200

#define NUM_REGS      16
#define NUM_KEYS      16
#define CARRY_REG     0xF
#define STACK_SIZE    16
#define WIDTH         64
#define HEIGHT        32
#define GFX_SIZE      WIDTH * HEIGHT  

const static uint8_t font_charset[CHARSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

struct cpu{
    uint8_t memory[MEM_SIZE];
    uint8_t V[NUM_REGS];
    uint8_t key[NUM_KEYS];
    uint8_t graphics[WIDTH * HEIGHT];
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t flags; 
    
    uint16_t opcode;
    uint16_t I;
    uint16_t pc;
    uint16_t stack[STACK_SIZE];
    uint16_t sp;
    
} cpu;
typedef struct cpu C8; 
 
C8* chip_8_init(); 
void disassemble_rom( C8* chip8, FILE *f);
void load_rom(C8* chip8, FILE *f ); 
void memory_write(C8* chip8, uint16_t address, uint8_t value); 
uint8_t memory_read(C8* chip8, uint16_t address);
void register_write(C8* chip8, uint8_t Vx, uint8_t value);
uint8_t register_read(C8* chip8, uint8_t Vx);  
uint16_t pc_read(C8* chip8); 
void fetch(); 
void decode(); 
void execute(); 
