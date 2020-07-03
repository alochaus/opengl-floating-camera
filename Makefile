CC=g++
CFLAGS=-Wall
LIBS=-lglfw3 -lGL -ldl -lpthread -lX11

SRC=glad.c main.cpp display.cpp shader.cpp input.cpp
OBJ=glad.o main.o display.o shader.o input.o

debuggable: CFLAGS += -g -DDEBUG
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

clean:
	rm *.o exe
