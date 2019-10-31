#include <stdio.h>
#include <stdint.h>
#include "../include/disassembler.h"

void disassemble(uint8_t *codebuffer, uint16_t pc)
{
    uint8_t *code = &codebuffer[pc];
    uint8_t upper_byte = code[0];
    uint8_t lower_byte = code[1];
    uint8_t upper_nibble = (upper_byte >> 4);
    uint8_t lower_nibble = (lower_byte & 0x0f);

    printf("| PC: %04x | Byte TWO : %02x | Byte ONE: %02x | (->) | ", pc, upper_byte, lower_byte);

    switch (upper_nibble)
    {
    case 0x00:
        switch (lower_byte)
        {
        case 0xe0:
            printf("%-10s", "CLS"); // //-10s handles spacing
            break;
        case 0xee:
            printf("%-10s", "RTS");
            break;
        default:
            printf("UNKNOWN 0");
            break;
        }
        break;
    case 0x01:
        printf("%-10s $%01x%02x", "JUMP", upper_byte & 0xf, lower_byte);
        break;
    case 0x02:
        printf("%-10s $%01x%02x", "CALL", upper_byte & 0xf, lower_byte);
        break;
    case 0x03:
        printf("%-10s V%01X|#$%02x", "SKIP.EQ", upper_byte & 0xf, lower_byte);
        break;
    case 0x04:
        printf("%-10s V%01X|#$%02x", "SKIP.NEQ", upper_byte & 0xf, lower_byte);
        break;
    case 0x05:
        printf("%-10s V%01X,V%01X", "SKIP.EQ", upper_byte & 0xf, lower_byte >> 4);
        break;
    case 0x06:
        printf("%-10s V%01X|#$%02x", "MVI", upper_byte & 0x0f, lower_byte);
        break;
    case 0x07:
        printf("%-10s V%01X|#$%02x", "ADI", upper_byte & 0xf, lower_byte);
        break;
    case 0x08:
    {
        switch (lower_nibble)
        {
        case 0:
            printf("%-10s V%01X,V%01X", "MOV.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 1:
            printf("%-10s V%01X,V%01X", "OR.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 2:
            printf("%-10s V%01X,V%01X", "AND.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 3:
            printf("%-10s V%01X,V%01X", "XOR.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 4:
            printf("%-10s V%01X,V%01X", "ADD.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 5:
            printf("%-10s V%01X,V%01X,V%01X", "SUB.", upper_byte & 0xf, upper_byte & 0xf, lower_byte >> 4);
            break;
        case 6:
            printf("%-10s V%01X,V%01X", "SHR.", upper_byte & 0xf, lower_byte >> 4);
            break;
        case 7:
            printf("%-10s V%01X,V%01X,V%01X", "SUB.", upper_byte & 0xf, lower_byte >> 4, lower_byte >> 4);
            break;
        case 0xe:
            printf("%-10s V%01X,V%01X", "SHL.", upper_byte & 0xf, lower_byte >> 4);
            break;
        default:
            printf("UNKNOWN 8");
            break;
        }
    }
    break;
    case 0x09:
        printf("%-10s V%01X,V%01X", "SKIP.NE", upper_byte & 0xf, lower_byte >> 4);
        break;
    case 0x0a:
        printf("%-10s I |#$%01x%02x", "MVI", upper_byte & 0x0f, lower_byte);
        break;
    case 0x0b:
        printf("%-10s $%01x%02x(V0)", "JUMP", upper_byte & 0xf, lower_byte);
        break;
    case 0x0c:
        printf("%-10s V%01X,#$%02X", "RNDMSK", upper_byte & 0xf, lower_byte);
        break;
    case 0x0d:
        printf("%-10s V%01X|V%01X|#$%01x", "SPRITE", upper_byte & 0xf, lower_byte >> 4, lower_byte & 0xf);
        break;
    case 0x0e:
        switch (lower_byte)
        {
        case 0x9E:
            printf("%-10s V%01X", "SKIPKEY.Y", lower_byte & 0xf);
            break;
        case 0xA1:
            printf("%-10s V%01X", "SKIPKEY.N", lower_byte & 0xf);
            break;
        default:
            printf("UNKNOWN E");
            break;
        }
        break;
    case 0x0f:
        switch (lower_byte)
        {
        case 0x07:
            printf("%-10s V%01X,DELAY", "MOV", upper_byte & 0xf);
            break;
        case 0x0a:
            printf("%-10s V%01X", "KEY", upper_byte & 0xf);
            break;
        case 0x15:
            printf("%-10s DELAY,V%01X", "MOV", upper_byte & 0xf);
            break;
        case 0x18:
            printf("%-10s SOUND,V%01X", "MOV", upper_byte & 0xf);
            break;
        case 0x1e:
            printf("%-10s I,V%01X", "ADI", upper_byte & 0xf);
            break;
        case 0x29:
            printf("%-10s I,V%01X", "SPRITECHAR", upper_byte & 0xf);
            break;
        case 0x33:
            printf("%-10s (I),V%01X", "MOVBCD", upper_byte & 0xf);
            break;
        case 0x55:
            printf("%-10s (I),V0-V%01X", "MOVM", upper_byte & 0xf);
            break;
        case 0x65:
            printf("%-10s V0-V%01X,(I)", "MOVM", upper_byte & 0xf);
            break;
        default:
            printf("UNKNOWN F");
            break;
        }
        break;
    }
}
