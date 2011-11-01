CC = g++
CFLAGS = -Wall
PROG = exec 
SRC = main.cc

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: thing.o bomb.o
	$(CC) $(CFLAGS) thing.o bomb.o header.h $(SRC) -o $(PROG) $(LIBS)
test: thing.o bomb.o
	$(CC) thing.o bomb.o header.h test.cc -o test
thing.o: thing.h 
	$(CC) -c thing.cc
bomb.o: bomb.h
	$(CC) -c bomb.cc
clean:
	rm *.o
	rm -f $(PROG)
