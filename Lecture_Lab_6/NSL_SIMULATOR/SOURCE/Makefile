CC = g++
CFLAGS = -O3 --std=c++17
AFLAGS = -L/opt/homebrew/lib -larmadillo #-L/opt/homebrew/Cellar/armadillo/12.8.1/lib -larmadillo
INC = -I/opt/homebrew/include #-I/opt/homebrew/Cellar/armadillo/12.8.1/include

all: Exercise_6.1.exe



Exercise_6.1.exe : system.o Exercise_6.1.o particle.o random.o function.o
	$(CC) function.o system.o particle.o random.o Exercise_6.1.o -o Exercise_6.1.exe $(AFLAGS)

Exercise_6.1.o : Exercise_6.1.cpp system.h particle.h function.h
	$(CC) -c Exercise_6.1.cpp -o Exercise_6.1.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS) $(INC)

particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)



clean :
	rm -f *.o *.exe

reset_es6:
	rm -f ../ES6/Ising/OUTPUT/*.*
	rm -f ../ES6/Ising/OUTPUT/CONFIG/*.*
