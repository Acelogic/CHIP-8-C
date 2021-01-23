#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"
#include "disassembler.h"

//Creates New Chip 8
 C8 *chip_8_init(){
    C8 *chip8 = malloc(sizeof(C8));
    chip8->opcode = 0;
    chip8->sp = 0;
    chip8->I = 0;
    chip8->flags = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->pc = PROGRAM_START;

    uint16_t i;
    for (i = 0; i < NUM_REGS; i++){
        register_write(chip8, i, 0);
        }
    for (i = 0; i < GFX_SIZE; i++){
        chip8->graphics[i] = 0;
        }
    for (i = 0; i < STACK_SIZE; i++){
        chip8->stack[i] = 0;
        }
    for (i = 0; i < NUM_KEYS; i++){
        chip8->key[i] = 0;
        }
    for (i = 0; i < MEM_SIZE; i++){
        memory_write(chip8, i, 0); 
        }
    for (i = 0; i < CHARSET_SIZE; i++) { 
        memory_write(chip8, CHARSET_START + i, font_charset[i]);
        }
    
    return chip8;
}

uint8_t memory_read(C8 *chip8, uint16_t address)
{
    printf("Read: 0x%X \n", chip8->memory[address]);
    return chip8->memory[address];
}
void memory_write(C8 *chip8, uint16_t address, uint8_t value)
{
    chip8->memory[address] = value;
    //printf("Written: 0x%X \n", value);
}

// register_read(Chip8, 0-F for V )
uint8_t register_read(C8 *chip8, uint8_t Vx)
{
    return chip8->V[Vx];
}
void register_write(C8 *chip8, uint8_t Vx, uint8_t value)
{
    chip8->V[Vx] = value;
}


uint16_t pc_read(C8 *chip8)
{
    return chip8->pc;
}
void pc_write(C8 *chip8, uint16_t value)
{
    chip8->pc = value;
}


uint16_t I_read(C8 *chip8)
{
    return chip8->I;
}
void I_write(C8 *chip8, uint16_t value)
{
    chip8->I = value;
}

uint8_t flag_read(C8 *chip8, uint8_t flag)
{
    return chip8->flags & flag;
}

void stack_push(C8 *chip8)
{
    chip8->stack[chip8->sp++] = pc_read(chip8);
}
void stack_pop(C8 *chip8)
{
    pc_write(chip8, chip8->stack[--chip8->sp]);
}

void disassemble_rom(C8 *chip8, FILE *f)
{
    //Get the file size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //CHIP-8 convention puts programs in memory at 0x200
    //They will all have hardcoded addresses expecting that
    //
   
    //Read the file into memory at 0x200 and close it.
    uint8_t *buffer = malloc(fsize + 0x200);
    fread(buffer + 0x200, fsize, 1, f);
    fclose(f);
    
    // Start the Disassemble Loop At Address 0x200 and increment the program counter
    while (chip8->pc < (fsize + 0x200))
    {
        disassemble(buffer, chip8->pc);
        chip8->pc += 2; // increment program counter by 2
        printf("\n");
    }
}

void load_rom(C8 *chip8, FILE *f){
    //Get the file size
    fseek(f, 0L, SEEK_END);
    int file_size = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //Check if file size is bigger than what memory can hold
    if (file_size > MEM_SIZE - PROGRAM_START)
    {
        fprintf(stderr, "ERROR: Not enough memory: %i\n", file_size);
        exit(1); 
    }

    //Allocate memory and store it in a buffer pointer
    uint8_t *buffer = malloc(file_size);

    //Copy contents of the file into the buffer
    fread(buffer, 1, file_size, f);
    fclose(f);

    //Write the contents of the buffer to memory
    for (uint16_t i = 0; i < file_size; i++)
    {
        memory_write(chip8, i + PROGRAM_START, buffer[i]);
    }

    printf("DEBUG: Rom loaded into RAM & memory.dump generated\n");
    chip8_mem_dump(chip8);
    chip8_debug(chip8);
}

void chip8_mem_dump(C8 *chip8){
    FILE *f = fopen("memory.dump", "wb");
    fwrite(chip8->memory, MEM_SIZE, 1, f);
    fclose(f);
}

void chip8_debug(C8 *chip8){
    fprintf(stderr, "\nop: 0x%04X pc: 0x%03X sp: 0x%02X I: 0x%03X\n", chip8->opcode, chip8->pc, chip8->sp, chip8->I);

    fprintf(stderr, "registers ");
    for (uint8_t i = 0; i < NUM_REGS; i++)
    {
        fprintf(stderr, "0x%02X ", register_read(chip8, i));
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "stack     ");
    if (chip8->sp == 0)
    {
        fprintf(stderr, "empty");
    }
    else
    {
        for (uint8_t i = 0; i < STACK_SIZE && i < chip8->sp; i++)
        {
            fprintf(stderr, "0x%03X ", chip8->stack[i]);
        }
    }
    fprintf(stderr, "\n");
    //    fprintf(stderr, "keys      ");
    //    for (uint8_t i=0; i<NUM_KEYS; i++) {
    //        if (chip8->keys[i] != 0) {
    //            fprintf(stderr, "%X ", i);
    //        }
    //    }
    fprintf(stderr, "\n\n");
}



