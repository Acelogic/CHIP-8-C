CC          = gcc 
CFLAGS      =
DEPS        = cpu.h disassembler.h
OBJ         = cpu.o dissasembler.o main.o
LD          = gcc 
CFLAG       = -Wall
SRC_DIR     = ./src


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

emu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: