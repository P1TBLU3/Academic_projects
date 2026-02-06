CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -O2
LDFLAGS=

all: program proceso stats_process

program: program.o menu.o input_usr.o collection.o item.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

proceso: proceso.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

stats_process: stats_process.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o program proceso stats_process
