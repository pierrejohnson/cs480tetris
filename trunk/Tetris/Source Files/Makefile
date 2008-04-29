.SUFFIXES:
.SUFFIXES: .cpp $(SUFFIXES)
CC = g++

OBJS=Hw3.o Matrix.o Block.o Tetris.o Camera.o

default:
	make Hw3

Hw3: $(OBJS)
	$(CC) -o Hw3.exe $(OBJS) -lglut32 -lopenal32 -lalut -lopengl32 -lglu32

.cpp.o:
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *~ Hw3