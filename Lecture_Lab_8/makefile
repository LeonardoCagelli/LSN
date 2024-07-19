CC = g++
CFLAGS = -O3 --std=c++17
AFLAGS = -L/opt/homebrew/lib -larmadillo #-L/opt/homebrew/Cellar/armadillo/12.8.1/lib -larmadillo
INC = -I/opt/homebrew/include #-I/opt/homebrew/Cellar/armadillo/12.8.1/include


make: Exercise_8.1.exe Exercise_8.2.exe




Exercise_8.1.exe: Exercise_8.1.o random.o class.o function.o
	$(CC) class.o random.o function.o Exercise_8.1.o -o Exercise_8.1.exe $(AFLAGS)

Exercise_8.1.o : Exercise_8.1.cpp class.h function.h 
	$(CC) -c Exercise_8.1.cpp -o Exercise_8.1.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

class.o : class.cpp class.h
	$(CC) -c class.cpp -o class.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)


Exercise_8.2.exe: Exercise_8.2.o random.o class.o function.o
	$(CC) class.o random.o function.o Exercise_8.2.o -o Exercise_8.2.exe $(AFLAGS)

Exercise_8.2.o : Exercise_8.2.cpp class.h function.h 
	$(CC) -c Exercise_8.2.cpp -o Exercise_8.2.o $(CFLAGS) $(INC)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS) $(INC)

class.o : class.cpp class.h
	$(CC) -c class.cpp -o class.o $(CFLAGS) $(INC)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS) $(INC)



clean:
	rm *.o 
	rm *.exe