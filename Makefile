
CC := gcc
BIN := wordle-es
SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=%.o)
CFLAGS := 
LDFLAGS :=

all: $(OBJ)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: clean
