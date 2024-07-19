CC = g++
CFLAGS = -Wall -O3 --std=c++11



all: Exercise_2.1.exe Exercise_2.2.exe

Exercise_2.1.exe : Exercise_2.1.o random.o function.o
	$(CC) random.o function.o Exercise_2.1.o -o Exercise_2.1.exe
Exercise_2.1.o : Exercise_2.1.cpp function.h 
	$(CC) -c Exercise_2.1.cpp -o Exercise_2.1.o $(CFLAGS)
function.o : function.cpp function.h 
	$(CC) -c function.cpp -o function.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

Exercise_2.2.exe : Exercise_2.2.o random.o class.o function.o
	$(CC) random.o function.o class.o Exercise_2.2.o -o Exercise_2.2.exe
Exercise_2.2.o : Exercise_2.2.cpp function.h class.h
	$(CC) -c Exercise_2.2.cpp -o Exercise_2.2.o $(CFLAGS)
function.o : function.cpp function.h 
	$(CC) -c function.cpp -o function.o $(CFLAGS)
class.o : class.cpp class.h
	$(CC) -c class.cpp -o class.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)


clean:
	rm *.o *.exe

