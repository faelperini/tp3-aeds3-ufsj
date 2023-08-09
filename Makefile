CC = gcc
CFLAGS = -Wall -Wextra -g

EXEC = tp3
SRC = main.c forcaBruta.c BMH.c KMP.c casos.c arquivos.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ) $(EXEC)
