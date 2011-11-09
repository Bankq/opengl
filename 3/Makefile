CC = g++
CFLAGS = -Wall
PROG = exec 
SRC = main.cc

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: ship.o 
	$(CC) $(CFLAGS) ship.o $(SRC) -o $(PROG) $(LIBS)
ship.o: ship.h 
	$(CC) -c ship.cc
clean:
	rm *.o
	rm -f $(PROG)
