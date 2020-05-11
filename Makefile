CC=g++
LIBS=-lglfw3 -lGL -lX11 -ldl -lpthread
OBJ=main.o glad.o

# g++ -c main.cpp -lglfw3 -lGL -lX11 -ldl -lpthread
# g++ -o exe main.o glad.o -lglfw3 -lGL -lX11 -ldl -lpthread

exe: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

glad.o: glad.c
	$(CC) -c $<

%.o: %.cpp
	$(CC) -c $<

clear:
	rm *.o exe
