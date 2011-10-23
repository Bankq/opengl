CC = g++
CFLAGS = -Wall
PROG = exec 
SRC = main.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: $(PROG)

$(PROG):	$(SRC)
	$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(LIBS)

clean:
	rm -f $(PROG)
