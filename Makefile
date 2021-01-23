TARGET = emu
CC = gcc
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

#Listing all source files using the * wildcard
SRC = $(wildcard $(SRC_DIR)/*.c)

#Listing all object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS  += -Wall -I 
LDFLAGS += -Llib
LDLIBS  += -lm

all: clean
		$(CC) $(CFLAGS) $(INC_DIR) $(SRC) -o $(TARGET)
		@printf "Making Program \n"
		@printf "\033[1;32m"
		@printf "Successfully created program"
		@printf "\033[0m\n"


clean:
	rm -f emu

