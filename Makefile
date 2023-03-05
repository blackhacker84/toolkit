# Makefile

CC = gcc
CFLAGS = -Wall
OBJS = command.o external.o

myprogram: $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o myprogram

command.o: command.c
    $(CC) $(CFLAGS) -c command.c

external.o: external.c
    $(CC) $(CFLAGS) -c external.c

.PHONY: clean
clean:
    rm -f $(OBJS) myprogram
