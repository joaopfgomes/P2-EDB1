CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = hash_table.o estatisticas.o main.o
EXEC = mega_sena

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

estatisticas.o: estatisticas.c estatisticas.h hash_table.h
	$(CC) $(CFLAGS) -c estatisticas.c

main.o: main.c hash_table.h estatisticas.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ) $(EXEC)
