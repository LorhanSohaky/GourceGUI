all: Utils DString

FLAGS = -Wall -c -I. -I./String/src -o

Utils:
	gcc utils.c $(FLAGS) ../obj/utils.o

DString:
	gcc String/src/dstring.c $(FLAGS) ../obj/dstring.o
