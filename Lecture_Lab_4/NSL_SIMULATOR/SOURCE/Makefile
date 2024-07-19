CC = g++
CFLAGS = -O3 --std=c++17
AFLAGS = -L/opt/homebrew/lib -larmadillo #-L/opt/homebrew/Cellar/armadillo/12.8.1/lib -larmadillo
INC = -I/opt/homebrew/include #-I/opt/homebrew/Cellar/armadillo/12.8.1/include

all: Exercise_4.2.exe Equilibration.exe



Exercise_4.2.exe : system.o Exercise_4.2.o particle.o random.o function.o
	$(CC) function.o system.o particle.o random.o Exercise_4.2.o -o Exercise_4.2.exe $(AFLAGS)

Exercise_4.2.o : Exercise_4.2.cpp system.h particle.h function.h
	$(CC) -c Exercise_4.2.cpp -o Exercise_4.2.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS) $(INC)

particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)



Equilibration.exe : system.o Equilibration.o particle.o random.o function.o
	$(CC) function.o system.o particle.o random.o Equilibration.o -o Equilibration.exe $(AFLAGS)

Equilibration.o : Equilibration.cpp system.h particle.h function.h
	$(CC) -c Equilibration.cpp -o Equilibration.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS) $(INC)

particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)


clean:
	rm *.o *.exe

reset_es4:
	rm -f *.o Exercise_4.2.exe
	rm -f ../ES4/Solid/OUTPUT/*.*
	rm -f ../ES4/Solid/OUTPUT/CONFIG/*.*
	rm -f ../ES4/Liquid/OUTPUT/*.*
	rm -f ../ES4/Liquid/OUTPUT/CONFIG/*.*
	rm -f ../ES4/Gas/OUTPUT/*.*
	rm -f ../ES4/Gas/OUTPUT/CONFIG/*.*

reset_eq4:
	rm -f *.o Equilibration.exe
	rm -f ../ES4/Equilibration/Solid/OUTPUT/*.*
	rm -f ../ES4/Equilibration/Solid/OUTPUT/CONFIG/*.*
	rm -f ../ES4/Equilibration/Liquid/OUTPUT/*.*
	rm -f ../ES4/Equilibration/Liquid/OUTPUT/CONFIG/*.*
	rm -f ../ES4/Equilibration/Gas/OUTPUT/*.*
	rm -f ../ES4/Equilibration/Gas/OUTPUT/CONFIG/*.*
