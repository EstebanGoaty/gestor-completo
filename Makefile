CC      = gcc
CFLAGS  = -Wall -Wextra -g
SRC     = $(wildcard *.c)
OBJ     = $(SRC:.c=.o)

gestor: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) gestor

.PHONY: clean
