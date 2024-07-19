CC = g++
CFLAGS = -Wall -O3 --std=c++11

all: Exercise_1.1.exe Exercise_1.2.exe Exercise_1.3.exe

Exercise_1.1.exe : Exercise_1.1.o random.o function.o
	$(CC) Exercise_1.1.o random.o function.o -o Exercise_1.1.exe

Exercise_1.1.o : Exercise_1.1.cpp
	$(CC) $(CFLAGS) -c Exercise_1.1.cpp -o Exercise_1.1.o

Exercise_1.2.exe : Exercise_1.2.o random.o function.o
	$(CC) Exercise_1.2.o random.o function.o -o Exercise_1.2.exe

Exercise_1.2.o : Exercise_1.2.cpp
	$(CC) $(CFLAGS) -c Exercise_1.2.cpp -o Exercise_1.2.o

Exercise_1.3.exe : Exercise_1.3.o random.o function.o
	$(CC) Exercise_1.3.o random.o function.o -o Exercise_1.3.exe

Exercise_1.3.o : Exercise_1.3.cpp
	$(CC) $(CFLAGS) -c Exercise_1.3.cpp -o Exercise_1.3.o

function.o : function.cpp function.h
	$(CC) $(CFLAGS) -c function.cpp -o function.o

random.o : random.cpp random.h
	$(CC) $(CFLAGS) -c random.cpp -o random.o

clean:
	rm -f *.o *.exe
