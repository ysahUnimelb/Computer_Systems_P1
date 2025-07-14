CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJ= main.o task1.o task2.o task3.o task4.o
EXEC=translate

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

task1.o: task1.c utils.h
	$(CC) $(CFLAGS) -c task1.c

task2.o: task2.c utils.h
	$(CC) $(CFLAGS) -c task2.c

task3.o: task3.c utils.h
	$(CC) $(CFLAGS) -c task3.c

task4.o: task4.c utils.h
	$(CC) $(CFLAGS) -c task4.c

clean:
	rm -f *.o $(EXEC)
