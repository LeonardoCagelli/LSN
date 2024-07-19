CC = g++
CFLAGS = -Wall -std=c++11

all: Exercise_9.1.exe

Exercise_9.1.exe: Exercise_9.1.o random.o class.o function.o
	$(CC) class.o random.o function.o Exercise_9.1.o -o Exercise_9.1.exe

Exercise_9.1.o: Exercise_9.1.cpp
	$(CC) -c Exercise_9.1.cpp -o Exercise_9.1.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

class.o: class.cpp class.h
	$(CC) -c class.cpp -o class.o $(CFLAGS)

function.o: function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)


clean:
	rm *.o
	rm *.exe
	rm OUTPUT/*.txt