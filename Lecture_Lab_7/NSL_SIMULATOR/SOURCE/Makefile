CC = g++
CFLAGS = -O3 --std=c++17
AFLAGS = -L/opt/homebrew/lib -larmadillo #-L/opt/homebrew/Cellar/armadillo/12.8.1/lib -larmadillo
INC = -I/opt/homebrew/include #-I/opt/homebrew/Cellar/armadillo/12.8.1/include

all: Exercise_7.2.exe Exercise_7.4.exe


Exercise_7.2.exe : system.o Exercise_7.2.o particle.o random.o function.o
	$(CC) function.o system.o particle.o random.o Exercise_7.2.o -o Exercise_7.2.exe $(AFLAGS)

Exercise_7.2.o : Exercise_7.2.cpp system.h particle.h function.h
	$(CC) -c Exercise_7.2.cpp -o Exercise_7.2.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS) $(INC)

particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)


Exercise_7.4.exe : system.o Exercise_7.4.o particle.o random.o function.o
	$(CC) function.o system.o particle.o random.o Exercise_7.4.o -o Exercise_7.4.exe $(AFLAGS)

Exercise_7.4.o : Exercise_7.4.cpp system.h particle.h function.h
	$(CC) -c Exercise_7.4.cpp -o Exercise_7.4.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS) $(INC)

particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)



reset_es72:
	rm -f *.o Exercise_7.2.exe
	rm -f ../Exercise_7.2/Solid/OUTPUT/*.*
	rm -f ../Exercise_7.2/Solid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.2/Liquid/OUTPUT/*.*
	rm -f ../Exercise_7.2/Liquid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.2/Gas/OUTPUT/*.*
	rm -f ../Exercise_7.2/Gas/OUTPUT/CONFIG/*.*



reset_es74:
	rm -f *.o Exercise_7.4.exe
	rm -f ../Exercise_7.4/MC/Solid/OUTPUT/*.*
	rm -f ../Exercise_7.4/MC/Solid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.4/MC/Liquid/OUTPUT/*.*
	rm -f ../Exercise_7.4/MC/Liquid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.4/MC/Gas/OUTPUT/*.*
	rm -f ../Exercise_7.4/MC/Gas/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.4/MD/Solid/OUTPUT/*.*
	rm -f ../Exercise_7.4/MD/Solid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.4/MD/Liquid/OUTPUT/*.*
	rm -f ../Exercise_7.4/MD/Liquid/OUTPUT/CONFIG/*.*
	rm -f ../Exercise_7.4/MD/Gas/OUTPUT/*.*
	rm -f ../Exercise_7.4/MD/Gas/OUTPUT/CONFIG/*.*