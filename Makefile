CC=g++
CFLAGS=-Wall
LIBS=-lSDL2 -lglfw3 -lGL -ldl

SRC=glad.c main.cpp display.cpp
OBJ=glad.o main.o display.o

debuggable: CFLAGS += -g
debuggable: exe

# g++ glad.c main.cpp display.cpp -lSDL2 -lglfw3 -lGL -ldl
# g++ -c main.cpp -lglfw3 -lGL -lX11 -ldl -lpthread
# g++ -o exe main.o glad.o -lglfw3 -lGL -lX11 -ldl -lpthread

exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

glad.o: glad.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clear:
	rm *.o exe
