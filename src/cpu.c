#include <stdio.h>
#include <stdint.h>
#include "cpu.h"

C8* chip_8_init(){
    
    C8* chip8 = malloc(sizeof(C8));
    chip8->opcode = 0;
    chip8->sp = 0;
    chip8->I = 0;
    chip8->flags = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->pc = 0;

    uint16_t i;
    for (i = 0; i < NUM_REGS; i++){register_write(chip8, i, 0);}
    for (i = 0; i < GFX_SIZE; i++){chip8->graphics[i] = 0;}
    for (i = 0; i < STACK_SIZE; i++) {chip8->stack[i] = 0;}
    for (i = 0; i < NUM_KEYS; i++){ chip8->key[i] = 0;}
    for (i = 0; i < MEM_SIZE; i++){memory_write(chip8, i, 0);}
    for (i = 0; i < CHARSET_SIZE; i++) { memory_write(chip8, CHARSET_START + i, font_charset[i]);}

    return chip8;
}

 void memory_write(C8* chip8, uint16_t address, uint8_t value){
    chip8->memory[address] = value;
}

 uint8_t memory_read(C8* chip8, uint16_t address) { 
    return chip8->memory[address]; 
}
 void register_write(C8* chip8, uint8_t Vx, uint8_t value){
    chip8->V[Vx] = value;
}

 uint8_t register_read(C8* chip8, uint8_t Vx) { 
    return chip8->V[Vx]; 
    }
 
 uint16_t pc_read(C8* chip8){ 
    return chip8->pc; 
}

void disassemble_rom(C8* chip8, FILE *f ){ 
    //Get the file size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //CHIP-8 convention puts programs in memory at 0x200
    // They will all have hardcoded addresses expecting that
    //
    //Read the file into memory at 0x200 and close it.
    uint8_t *buffer = malloc(fsize + 0x200);
    fread(buffer + 0x200, fsize, 1, f);
    fclose(f);
    
      
    chip8 -> pc = 0x200;
     
    while (chip8 -> pc < (fsize + 0x200))
    {
        disassemble(buffer, chip8 -> pc);
        chip8 -> pc += 2; // increment program counter by 2
        printf("\n");
    }

    //printf("Final Program Counter:%04x \n",  pc_read(chip8));

}

void load_rom(C8* chip8, FILE *f ){ 
     //Get the file size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //CHIP-8 convention puts programs in memory at 0x200
    // They will all have hardcoded addresses expecting that
    //
    //Read the file into memory at 0x200 and close it.
    *chip8 -> memory = malloc(fsize + 0x200);
    fread(chip8 -> memory + 0x200, fsize, 1, f);
    fclose(f);  

    printf("%04x", memory_read(chip8, 0x200)); 
}

void fetch(); 
void decode(); 
void execute(); 
