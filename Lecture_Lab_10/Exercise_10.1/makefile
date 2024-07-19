# CXX = mpicxx
# CXXFLAGS = -I/opt/homebrew/include
# LDFLAGS = -L/opt/homebrew/lib -larmadillo

# TARGET = armadillo_mpi_example
# SRCS = armadillo_mpi_example.cpp

# $(TARGET): $(SRCS)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# clean:
# 	rm -f $(TARGET)

CXX = mpicxx
CXXFLAGS = -Wall -std=c++11 -I/opt/homebrew/include

all: Exercise_10.1.exe

Exercise_10.1.exe: Exercise_10.1.o random.o class.o function.o
	$(CXX) Exercise_10.1.o random.o class.o function.o -o Exercise_10.1.exe $(CXXFLAGS)

Exercise_10.1.o: Exercise_10.1.cpp
	$(CXX) -c Exercise_10.1.cpp -o Exercise_10.1.o $(CXXFLAGS)

random.o: random.cpp random.h
	$(CXX) -c random.cpp -o random.o $(CXXFLAGS)

class.o: class.cpp class.h
	$(CXX) -c class.cpp -o class.o $(CXXFLAGS)

function.o: function.cpp function.h
	$(CXX) -c function.cpp -o function.o $(CXXFLAGS)

clean:
	rm -f *.o
	rm -f Exercise_10.1.exe
	rm -f OUTPUT/*.txt

# To execute the program run: mpiexec -n 4 ./main.exe

