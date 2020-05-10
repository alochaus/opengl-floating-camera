CC=g++
LIBS=-Wall -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
OBJ=main.o

exe: $(OBJ)
	$(CC) $(LIBS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) -c $<

clear:
	rm *.o exe
