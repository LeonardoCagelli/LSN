CC = g++
CFLAGS = -Wall -O3 --std=c++11 -g

all: Exercise_3.1.exe 

Exercise_3.1.exe : Exercise_3.1.o random.o
	$(CC) random.o Exercise_3.1.o -o Exercise_3.1.exe
Exercise_3.1.o : Exercise_3.1.cpp 
	$(CC) -c Exercise_3.1.cpp -o Exercise_3.1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

clean:
	rm *.exe *.o