TARGET = emu

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj 

#Listing all source files using the * wildcard
SRC = $(wildcard $(SRC_DIR)/*.c)

#Listing all includes
INC = $(wildcard $(INC_DIR)/*.h)

#Listing all object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS  += -Wall -I$(INC)
LDFLAGS += -Llib
LDLIBS  += -lm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR) := $(notdir $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c)))

clean: 
	$(RM) $(OBJ)

.PHONY: all clean